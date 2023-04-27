#include "common/global.h"
#include "render.h"
#include "tcp.h"
#include "kcp.h"
#include "export.h"
#include <filesystem>
#include <fstream>
#include <cstdlib>

Render::Render() {
  finalized_ = true;
  pid_ = GetCurrentProcessId();
}

Render::~Render() {
  CL_TAG();
}

void Render::ResponseLoop() {
  CL_LOG("start response loop thread=%d", GetCurrentThreadId());
  bool ret = false;

  while (!finalized_) {
    RenderResponse* render_response = new RenderResponse;
    ret = socket_->Read(&render_response->header, sizeof(RenderResponseHeader));
    if (!ret) {
      break;
    }

    if (render_response->header.size > 0) {
      render_response->data.resize(render_response->header.size);
      ret = socket_->Read(render_response->data.data(), render_response->data.size());
      if (!ret) {
        break;
      }

      if (render_response->header.decompress == ZSTD_COMPRESS_TYPE) {
        render_response->data = std::move(zstd_->Decompress(render_response->data));
      }
    }

    auto& response = responses_[render_response->header.tid];
    response.render_response = render_response;
    SetEvent(response.event);
  }

  if (!ret && !finalized_) {
    CL_ERROR("read error happened");
    finalized_ = true;
  }
  CL_LOG("response loop end");
}

void Render::Quit() {
  finalized_ = true;
  
  // if windows socket resource dll was unloaded before, it may cause assert exception in debug mode.
  if (socket_) {
    delete socket_;
    socket_ = nullptr;
  }

  if (zstd_) {
    delete zstd_;
    zstd_ = nullptr;
  }

  for (auto iter = responses_.begin(); iter != responses_.end(); iter++) {
    SetEvent(iter->second.event);
  }
  responses_.clear();

  if (response_loop_.joinable()) {
    response_loop_.join();
  }
}

void Render::Run(std::string host, std::string port) {
  CL_ASSERT(finalized_);
  finalized_ = false;

  auto net = std::getenv("CLINK_NET");
  if (!net) {
    CL_ERROR("get net env failed");
    return;
  }

  if (strcmp(net, "tcp") == 0) {
    socket_ = new Tcp(io_context_);
  } else if (strcmp(net, "kcp") == 0) {
    socket_ = new Kcp(io_context_);
  }
  
  if (!socket_) {
    CL_ERROR("init socket error");
    return;
  }

  if (!socket_->Connect(host, port)) {
    CL_ERROR("connect remote error");
    return;
  }

  response_loop_ = std::thread(&Render::ResponseLoop, this);
  zstd_ = new ZSTDUtil(ZSTD_COMPRESS_WORKER_NUM, ZSTD_COMPRESS_LEVEL, ZSTD_COMPRESS_WINDOW_POWER);
}

bool Render::LoadCudaKernelFunctionsFromCuBin(CUlinkState link_state, void* bin, size_t size) {
  std::string_view data((char*)bin, size);
  std::hash<std::string_view> hasher;
  auto hash = hasher(data);
  link_hashs_[link_state].insert(hash);
  if (hash_function_params_.find(hash) != hash_function_params_.end()) {
    return true;
  }

  // check cuobjdump tool exists
  std::string cuobjdump_path = "d:\\cuobjdump.exe";
  if (!std::filesystem::exists(cuobjdump_path)) {
    CL_ERROR("cuobjdump tool not exists path=%s", cuobjdump_path.c_str());
    return false;
  }

  // save bin to tmp file
  auto bin_file_path = std::filesystem::temp_directory_path() / (GenerateRandomString(10) + "_cu.bin");
  std::ofstream bin_file(bin_file_path, std::ios::binary);
  if (!bin_file.is_open()) {
    CL_ERROR("failed to create bin file=%s", bin_file_path.string().c_str());
    return false;
  }
  bin_file.write(data.data(), data.size());
  bin_file.close();

  // call cuobjdump tool to get bin file information
  char line[1024];
  bool start = false, result = false;
  std::string current_function;
  std::string command = "cmd /c " + cuobjdump_path + " --dump-elf " + bin_file_path.string();
  auto& func_params = hash_function_params_[hash];
  
  FILE* pipe = _popen(command.c_str(), "r");
  if (!pipe) {
    CL_ERROR("failed to dump bin file cmd=%s", command.c_str());
    goto clean;
  }

  while (!feof(pipe)) {
    if (fgets(line, sizeof(line), pipe) == nullptr) {
      break;
    }

    std::string line_str = line;
    if (line_str.compare(0, 9, ".nv.info.") == 0) {
      line_str.pop_back(); // delete '\n'
      current_function = line_str.substr(9);
      CL_ASSERT(func_params.find(current_function) == func_params.end());
      if (!start) {
        start = true;
      }
      std::deque<size_t> params;
      func_params.insert(std::make_pair(current_function, std::move(params)));
    } else if (line_str.compare(0, 27, "\tValue:\tIndex : 0x0\tOrdinal") == 0) {
      line_str.pop_back(); // delete '\n'
      auto size = std::stoi(line_str.substr(line_str.size() - 3), nullptr, 16);
      func_params[current_function].push_front(size);
    }

    if (line_str == ".nv.callgraph\n" && start) {
      break;
    }
  }
  _pclose(pipe);
  result = true;

clean:
  if (std::filesystem::exists(bin_file_path)) {
    std::filesystem::remove(bin_file_path);
  }
  return result;
}

CUresult Render::PrepareRequest(RenderRequest* request) {
  auto cuda = (CudaRequest*)request->datas[0].data();

  switch (cuda->api_index) {
    case CUGETERRORSTRING: {
      auto error_str = (const char**)cuda->params[1];
      *error_str = ErrorDescription((CUresult)cuda->params[0]);
      return CUDA_SUCCESS;
    }
    case CULINKCREATE: {
      auto num_option = (unsigned int)cuda->params[0];
      if (num_option > 0) {
        std::string_view options((char*)cuda->params[1], num_option * sizeof(CUjit_option));
        request->header.size += (uint32_t)options.size();
        request->datas.emplace_back(std::move(options));

        std::string_view values((char*)cuda->params[2], num_option * sizeof(void*));
        request->header.size += (uint32_t)values.size();
        request->datas.emplace_back(std::move(values));
      }
      break;
    }
    case CULINKADDDATA: {
      request->header.sync = false;
      auto type = (CUjitInputType)cuda->params[1];
      switch (type) {
      case CU_JIT_INPUT_CUBIN:
        if (!LoadCudaKernelFunctionsFromCuBin((CUlinkState)cuda->params[0], (void*)cuda->params[2], cuda->params[3])) {
          CL_ERROR("failed to load cuda functions from cubin");
          return CUDA_ERROR_INVALID_VALUE;
        }
        break;
      default:
        CL_LOG("add link data type=%d", type);
        break;
      }

      std::string_view data((char*)cuda->params[2], cuda->params[3]);
      request->header.size += (uint32_t)data.size();
      request->datas.emplace_back(std::move(data));

      auto num_option = (unsigned int)cuda->params[5];
      if (num_option > 0) {
        std::string_view options((char*)cuda->params[6], num_option * sizeof(CUjit_option));
        request->header.size += (uint32_t)options.size();
        request->datas.emplace_back(std::move(options));

        std::string_view values((char*)cuda->params[7], num_option * sizeof(void*));
        request->header.size += (uint32_t)values.size();
        request->datas.emplace_back(std::move(values));
      }

      auto name = (char*)cuda->params[4];
      if (name) {
        std::string_view name_sv(name, strlen(name) + 1);
        request->header.size += (uint32_t)name_sv.size();
        request->datas.emplace_back(std::move(name_sv));
      }
      break;
    }
    case CUMODULEGETGLOBAL: {
      auto name = (char*)cuda->params[3];
      if (name) {
        std::string_view name_sv(name, strlen(name) + 1);
        request->header.size += (uint32_t)name_sv.size();
        request->datas.emplace_back(std::move(name_sv));
      }
      break;
    }
    case CUMODULEGETFUNCTION:
    case CUMODULEGETTEXREF: {
      auto name = (char*)cuda->params[2];
      std::string_view name_sv(name, strlen(name) + 1);
      request->header.size += (uint32_t)name_sv.size();
      request->datas.emplace_back(std::move(name_sv));
      break;
    }
    case CUMEMCPYHTOD:
    case CUMEMCPYHTODASYNC: {
      std::string_view host((char*)cuda->params[1], cuda->params[2]);
      request->header.size += (uint32_t)host.size();
      request->datas.emplace_back(std::move(host));
      request->header.sync = false;
      break;
    }
    case CULAUNCHKERNEL: {
      request->header.sync = false;
      auto kernel_params = (void**)cuda->params[9];
      if (!kernel_params) {
        break;
      }

      auto& info = function_infos_[(CUfunction)cuda->params[0]];
      auto iter1 = module_images_.find(info.module);
      if (iter1 == module_images_.end()) {
        CL_PANIC("can't find the module=%p", info.module);
        return CUDA_ERROR_INVALID_VALUE;
      }

      auto iter2 = image_links_.find(iter1->second);
      if (iter2 == image_links_.end()) {
        CL_PANIC("can't find the link image=%p", iter1->second);
        return CUDA_ERROR_INVALID_VALUE;
      }

      auto iter3 = link_hashs_.find(iter2->second);
      if (iter3 == link_hashs_.end()) {
        CL_PANIC("can't find the cubin hash link=%p", iter2->second);
        return CUDA_ERROR_INVALID_VALUE;
      }

      bool find = false;
      for (auto& hash : iter3->second) {
        auto iter4 = hash_function_params_.find(hash);
        if (iter4 != hash_function_params_.end()) {
          auto iter5 = iter4->second.find(info.name);
          if (iter5 != iter4->second.end()) {
            find = true;
            auto& params = iter5->second;
            auto kernel_param_count = params.size();
            CL_LOG("launch kernel function=%s param_count=%d", info.name.c_str(), kernel_param_count);

            std::string kernel_param_count_string((char*)&kernel_param_count, sizeof(size_t));
            request->header.size += (uint32_t)kernel_param_count_string.size();
            request->datas.emplace_back(std::move(kernel_param_count_string));

            std::string_view kernel_params_sv((char*)kernel_params, kernel_param_count * sizeof(void*));
            request->header.size += (uint32_t)kernel_params_sv.size();
            request->datas.emplace_back(std::move(kernel_params_sv));

            for (size_t i = 0; i < kernel_param_count; i++) {
              // FIXME: this method to check address from guest or host is unstable, save all host pointer to check may be better.
              if (IsAddressValid(kernel_params[i])) {
                std::string kernel_param_size_string((char*)&params[i], sizeof(size_t));
                request->header.size += (uint32_t)kernel_param_size_string.size();
                request->datas.emplace_back(std::move(kernel_param_size_string));

                std::string_view param_value((char*)kernel_params[i], params[i]);
                request->header.size += (uint32_t)param_value.size();
                request->datas.emplace_back(std::move(param_value));
              } else {
                // for host pointer address, set the size=0, nothing to copy
                CL_ASSERT(params[i] == sizeof(uint64_t));
                request->header.size += (uint32_t)sizeof(uint64_t);
                request->datas.emplace_back(std::move(std::to_string(0)));
              }
            }
            break;
          }
        }
      }

      if (!find) {
        CL_PANIC("can't find the func=%s", info.name.c_str());
        return CUDA_ERROR_INVALID_VALUE;
      }
      break;
    }
    case CUARRAYCREATE: {
      std::string_view create((char*)cuda->params[1], sizeof(CUDA_ARRAY_DESCRIPTOR));
      request->header.size += (uint32_t)create.size();
      request->datas.emplace_back(std::move(create));
      break;
    }
    case CUARRAY3DCREATE: {
      std::string_view create((char*)cuda->params[1], sizeof(CUDA_ARRAY3D_DESCRIPTOR));
      request->header.size += (uint32_t)create.size();
      request->datas.emplace_back(std::move(create));
      break;
    }
    case CUMEMCPY2D:
    case CUMEMCPY2DASYNC: {
      auto copy = (CUDA_MEMCPY2D*)cuda->params[0];
      std::string_view copy_sv((char*)copy, sizeof(CUDA_MEMCPY2D));
      request->header.size += (uint32_t)copy_sv.size();
      request->datas.emplace_back(std::move(copy_sv));

      if (copy->srcMemoryType == CU_MEMORYTYPE_HOST) {
        if (copy->srcPitch == copy->WidthInBytes) {
          std::string_view data((char*)copy->srcHost, copy->WidthInBytes * copy->Height);
          request->header.size += (uint32_t)data.size();
          request->datas.emplace_back(std::move(data));
        } else {
          for (size_t h = 0; h < copy->Height; h++) {
          std::string_view data((char*)copy->srcHost + h * copy->srcPitch, copy->WidthInBytes);
            request->header.size += (uint32_t)data.size();
            request->datas.emplace_back(std::move(data));
          }
        }
        CL_LOG("copy from cpu=0x%llx to gpu=0x%llx", copy->srcHost, copy->dstDevice);
      }

      if (copy->dstMemoryType != CU_MEMORYTYPE_HOST) {
        request->header.sync = false;
      }
      break;
    }
    case CUMEMCPY3D: {
      auto copy = (CUDA_MEMCPY3D*)cuda->params[0];
      std::string_view copy_sv((char*)copy, sizeof(CUDA_MEMCPY3D));
      request->header.size += (uint32_t)copy_sv.size();
      request->datas.emplace_back(std::move(copy_sv));

      if (copy->srcMemoryType == CU_MEMORYTYPE_HOST) {
        if (copy->srcPitch == copy->WidthInBytes) {
          std::string_view data((char*)copy->srcHost, copy->WidthInBytes * copy->Height * copy->Depth);
          request->header.size += (uint32_t)data.size();
          request->datas.emplace_back(std::move(data));
        } else {
          for (size_t z = 0; z < copy->Depth; z++) {
            for (size_t h = 0; h < copy->Height; h++) {
              std::string_view data((char*)copy->srcHost + z * h * copy->srcPitch + h * copy->srcPitch, copy->WidthInBytes);
              request->header.size += (uint32_t)data.size();
              request->datas.emplace_back(std::move(data));
            }
          }
        }
      }

      if (copy->dstMemoryType != CU_MEMORYTYPE_HOST) {
        request->header.sync = false;
      }
      break;
    }
    case CUMEMHOSTGETDEVICEPOINTER: {
      auto guest = (void*)cuda->params[1];
      auto iter = guest_host_memory_.find(guest);
      if (iter != guest_host_memory_.end()) {
        cuda->params[1] = (uint64_t)iter->second;
      }
      break;
    }
    case CUMEMFREEHOST:
    case CUMEMCPYDTOH: {
      auto guest = (void*)cuda->params[0];
      auto iter = guest_host_memory_.find(guest);
      if (iter != guest_host_memory_.end()) {
        cuda->params[0] = (uint64_t)iter->second;
      }
      break;
    }
    case CUTEXOBJECTCREATE: {
      auto res_desc = (CUDA_RESOURCE_DESC*)cuda->params[1];
      if (res_desc) {
        std::string_view res_desc_sv((char*)res_desc, sizeof(CUDA_RESOURCE_DESC));
        request->header.size += (uint32_t)res_desc_sv.size();
        request->datas.emplace_back(std::move(res_desc_sv));
      }

      auto tex_desc = (CUDA_TEXTURE_DESC*)cuda->params[2];
      if (tex_desc) {
        std::string_view tex_desc_sv((char*)tex_desc, sizeof(CUDA_TEXTURE_DESC));
        request->header.size += (uint32_t)tex_desc_sv.size();
        request->datas.emplace_back(std::move(tex_desc_sv));
      }

      auto view_desc = (CUDA_RESOURCE_VIEW_DESC*)cuda->params[3];
      if (view_desc) {
        std::string_view view_desc_sv((char*)view_desc, sizeof(CUDA_RESOURCE_VIEW_DESC));
        request->header.size += (uint32_t)view_desc_sv.size();
        request->datas.emplace_back(std::move(view_desc_sv));
      }
      break;
    }
    case CUINIT:
    case CUCTXDESTROY:
    case CUCTXPUSHCURRENT:
    case CUCTXSETCURRENT:
    case CULINKDESTROY:
    case CUMODULEUNLOAD:
    case CUFUNCSETCACHECONFIG:
    case CUMEMHOSTUNREGISTER:
    case CUEVENTDESTROY:
    case CUEVENTRECORD:
    case CUMEMCPYDTOD:
    case CUMEMFREE:
    case CUTEXREFSETFORMAT:
    case CUTEXREFSETADDRESSMODE:
    case CUTEXREFSETFILTERMODE:
    case CUTEXREFSETFLAGS:
    case CUTEXOBJECTDESTROY:
    case CUTEXREFSETARRAY:
    case CUARRAYDESTROY:
    case CUMEMSETD8ASYNC:
      request->header.sync = false;
      break;
    default:
      break;
  }

  if (request->header.size > ZSTD_COMPRESS_DATA_MIN_SIZE) {
    request->header.compress = ZSTD_COMPRESS_TYPE;
  }

  // continue sending requeust to remote
  return CUDA_ERROR_UNKNOWN;
}

CUresult Render::HandleResponse(RenderRequest* request, RenderResponse* response) {
  auto cuda = (CudaRequest*)request->datas[0].data();
  auto result = (CUresult)response->header.result;

  if (result != CUDA_SUCCESS) {
    CL_ERROR("handle error for api=%s result=%d", GetCudaFunctionName(cuda->api_index), result);
    goto end;
  }

  switch (cuda->api_index) {
    case CUDRIVERGETVERSION:
    case CUDEVICEGETCOUNT:
    case CUDEVICEGETATTRIBUTE:
    case CUFUNCGETATTRIBUTE:
      if (cuda->params[0]) {
        *(int*)cuda->params[0] = *(int*)response->data.data();
      }
      break;
    case CUMODULELOADDATA: {
      auto module = *(CUmodule*)response->data.data();
      module_images_[module] = (void*)cuda->params[1];
      *(CUmodule*)cuda->params[0] = module;
      break;
    }
    case CUDEVICEGET:
    case CUCTXCREATE:
    case CUCTXPOPCURRENT:
    case CUDEVICETOTALMEM:
    case CUMODULEGETTEXREF:
    case CUMEMHOSTGETDEVICEPOINTER:
    case CUMEMALLOC:
    case CUEVENTCREATE:
    case CUTEXREFSETADDRESS:
    case CUARRAYCREATE:
    case CUARRAY3DCREATE:
    case CUTEXOBJECTCREATE:
    case CUSTREAMCREATE:
      if (cuda->params[0]) {
        *(uint64_t*)cuda->params[0] = *(uint64_t*)response->data.data();
      }
      break;
    case CUDEVICEGETNAME:
    case CUDEVICEGETUUID:
      memcpy((char*)cuda->params[0], response->data.data(), response->data.size());
      break;
    case CUDEVICECOMPUTECAPABILITY: {
      auto ret = (int*)response->data.data();
      *(int*)cuda->params[0] = ret[0];
      *(int*)cuda->params[1] = ret[1];
      break;
    }
    case CUMEMGETINFO:
    case CUMEMALLOCPITCH: {
      auto ret = (uint64_t*)response->data.data();
      if (cuda->params[0]) {
        *(uint64_t*)cuda->params[0] = ret[0];
      }
      if (cuda->params[1]) {
        *(uint64_t*)cuda->params[1] = ret[1];
      }
      break;
    }
    case CULINKCREATE:
      *(uint64_t*)cuda->params[3] = *(uint64_t*)response->data.data();
      break;
    case CULINKCOMPLETE: {
      auto ret = (uint64_t*)response->data.data();
      auto image = (void*)ret[0];
      auto size = (size_t)ret[1];

      *(void**)cuda->params[1] = image;
      if (cuda->params[2]) {
        *(size_t*)cuda->params[2] = size;
      }
      image_links_[image] = (CUlinkState)cuda->params[0];
      break;
    }
    case CUMODULEGETGLOBAL:
      *(uint64_t*)cuda->params[0] = *(uint64_t*)response->data.data();
      if (cuda->params[1]) {
        *(uint64_t*)cuda->params[1] = *(uint64_t*)(response->data.data() + sizeof(uint64_t));
      }
      break;
    case CUMODULEGETFUNCTION: {
      auto function = *(CUfunction*)response->data.data();
      *(CUfunction*)cuda->params[0] = function;

      CuFunctionInfo info;
      info.module = (CUmodule)cuda->params[1];
      info.name = (const char*)cuda->params[2];
      function_infos_[function] = std::move(info);
      break;
    }
    case CUMEMCPY2D:
    case CUMEMCPY2DASYNC: {
      auto copy = (CUDA_MEMCPY2D*)cuda->params[0];
      if (copy->dstMemoryType == CU_MEMORYTYPE_HOST) {
        for (size_t h = 0; h < copy->Height; h++) {
          memcpy((char*)copy->dstHost + h * copy->dstPitch, response->data.data() + h * copy->WidthInBytes, copy->WidthInBytes);
        }
        CL_LOG("copy from gpu=0x%llx to cpu=0x%llx", copy->srcDevice, copy->dstHost);
      }
      break;
    }
    case CUMEMCPY3D: {
      auto copy = (CUDA_MEMCPY3D*)cuda->params[0];
      if (copy->dstMemoryType == CU_MEMORYTYPE_HOST) {
        for (size_t z = 0; z < copy->Depth; z++) {
          for (size_t h = 0; h < copy->Height; h++) {
            memcpy((char*)copy->dstHost + z * h * copy->dstPitch + h * copy->dstPitch,
              (char*)response->data.data() + z * h * copy->WidthInBytes + h * copy->WidthInBytes,
              copy->WidthInBytes);
          }
        }
      }
      break;
    }
    case CUMEMHOSTALLOC: {
      auto host = *(void**)response->data.data();
      auto guest = VirtualAlloc(NULL, (size_t)cuda->params[1], MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
      guest_host_memory_[guest] = host;
      host_guest_memory_[host] = guest;
      *(void**)cuda->params[0] = guest;
      break;
    }
    case CUMEMFREEHOST: {
      auto host = (void*)cuda->params[0];
      auto iter = host_guest_memory_.find(host);
      if (iter != host_guest_memory_.end()) {
        auto guest = iter->second;
        host_guest_memory_.erase(iter);
        guest_host_memory_.erase(guest);
        VirtualFree(guest, 0, MEM_RELEASE);
      }
      break;
    }
    case CUMEMCPYDTOH: {
      auto host = (void*)cuda->params[0];
      auto iter = host_guest_memory_.find(host);
      if (iter == host_guest_memory_.end()) {
        CL_LOG("write host=%p size=%lld directly", host, response->data.size());
        memcpy(host, response->data.data(), response->data.size());
      } else {
        CL_LOG("write guest=%p host=%p size=%lld", iter->first, iter->second, response->data.size());
        memcpy(iter->second, response->data.data(), response->data.size());
      }
      break;
    }
    default:
      break;
  }

  CL_LOG("finish api=%s param_count=%d tid=%d", GetCudaFunctionName(cuda->api_index), cuda->param_count, request->header.tid);

end:
  // finish this trnasport process
  delete request;
  delete response;

  return result;
}

CUresult Render::Dispatch(uint32_t index, uint32_t count, ...) {
  if (finalized_) {
    return CUDA_ERROR_UNKNOWN;
  }

  // set cuda request params
  std::string params(sizeof(CudaRequest) + sizeof(uint64_t) * count, '\0');
  params.resize(sizeof(CudaRequest) + sizeof(uint64_t) * count);
  auto cuda = (CudaRequest*)params.data();
  cuda->api_index = index;
  cuda->param_count = count;
  cuda->version = CUDA_VERSION;
  if (cuda->param_count > 0) {
    va_list args;
    va_start(args, count);
    for (size_t i = 0; i < count; i++) {
      // ATTENTION: we assume that each cuda api param size was less than or equal to 8 bytes
      cuda->params[i] = va_arg(args, uint64_t);
    }
    va_end(args);
  }

  RenderRequest* request = new RenderRequest;
  request->header.size = (uint32_t)params.size();
  request->header.pid = pid_;
  request->header.tid = GetCurrentThreadId();
  request->header.render = RENDER_CUDA;
  request->header.compress = NO_COMPRESS;
  request->header.sync = true;
  request->datas.emplace_back(std::move(params));

  CL_LOG("call api=%s param_count=%d tid=%d", GetCudaFunctionName(cuda->api_index), cuda->param_count, request->header.tid);

  auto result = PrepareRequest(request);
  if (result == CUDA_SUCCESS) {
    CL_LOG("finish api=%s tid=%d success directly", GetCudaFunctionName(cuda->api_index), request->header.tid);
    return CUDA_SUCCESS;
  } else if (result == CUDA_ERROR_INVALID_VALUE) {
    CL_LOG("failed to prepare request api=%s tid=%d", GetCudaFunctionName(cuda->api_index), request->header.tid);
    return CUDA_ERROR_INVALID_VALUE;
  }

  // create response for current thread
  auto& response = responses_[request->header.tid];
  if (response.event == nullptr) {
    response.event = CreateEvent(nullptr, false, false, nullptr);
    CL_ASSERT(response.event != nullptr);
  }

  // send request
  auto ret = false;
  if (request->header.compress == ZSTD_COMPRESS_TYPE) {
    std::string compressed_data = std::move(zstd_->Compress(request->datas));
    request->header.size = (uint32_t)compressed_data.size();
    ret = socket_->Write(&request->header, sizeof(RenderRequestHeader));
    if (ret) {
      ret = socket_->Write(compressed_data.data(), compressed_data.size());
    }
  } else {
    ret = socket_->Write(&request->header, sizeof(RenderRequestHeader));
    if (ret) {
      for (auto& data : request->datas) {
        ret = socket_->Write(data.data(), data.size());
        if (!ret) {
          break;
        }
      }
    }
  }

  if (!ret) {
    if (!finalized_) {
      CL_ERROR("write err happened");
      finalized_ = true;
    }

    delete request;
    return CUDA_ERROR_UNKNOWN;
  }

  if (!request->header.sync) {
    CL_LOG("finish api=%s tid=%d success without sync", GetCudaFunctionName(cuda->api_index), request->header.tid);
    delete request;
    return CUDA_SUCCESS;
  }

  // wait for response from socket
  WaitForSingleObject(response.event, INFINITE);

  if (finalized_) {
    delete request;
    delete response.render_response;
    return CUDA_ERROR_UNKNOWN;
  }

  // handle response in current thread
  return HandleResponse(request, response.render_response);
}
