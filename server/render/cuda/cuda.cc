
#include "cuda.h"
#include "logger.h"
#include "utilities.h"
#include <cstring>

Cuda::Cuda(uint32_t version, uint64_t pid, uint64_t tid) {
  version_ = version;
  pid_ = pid;
  tid_ = tid;
}

Cuda::~Cuda() {
}

void Cuda::DispatchCuInit(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuInit(request->params[0]);
}

void Cuda::DispatchCuDriverGetVersion(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = sizeof(int);
  response->data.resize(response->header.size);
  response->header.result = cuDriverGetVersion((int*)response->data.data());
}

void Cuda::DispatchCuDeviceGetCount(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = sizeof(int);
  response->data.resize(response->header.size);
  response->header.result = cuDeviceGetCount((int*)response->data.data());
}

void Cuda::DispatchCuDeviceGet(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = sizeof(CUdevice);
  response->data.resize(response->header.size);
  response->header.result = cuDeviceGet((CUdevice*)response->data.data(), request->params[1]);
}

void Cuda::DispatchCuDeviceGetName(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = (int)request->params[1];
  response->data.resize(response->header.size);
  response->header.result = cuDeviceGetName((char*)response->data.data(), request->params[1], request->params[2]);
}

void Cuda::DispatchCuDeviceComputeCapability(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = sizeof(int) * 2;
  response->data.resize(response->header.size);

  auto ret = (int*)response->data.data();
  response->header.result = cuDeviceComputeCapability(&ret[0], &ret[1], (CUdevice)request->params[2]);
}

void Cuda::DispatchCuDeviceGetAttribute(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = sizeof(int);
  response->data.resize(response->header.size);
  response->header.result = cuDeviceGetAttribute((int*)response->data.data(), (CUdevice_attribute)request->params[1], (CUdevice)request->params[2]);
}

void Cuda::DispatchCuDeviceTotalMem(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = sizeof(size_t);
  response->data.resize(response->header.size);
  response->header.result = cuDeviceTotalMem((size_t*)response->data.data(), (CUdevice)request->params[1]);
}

void Cuda::DispatchCuDeviceGetUuid(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = sizeof(CUuuid);
  response->data.resize(response->header.size);
  response->header.result = cuDeviceGetUuid((CUuuid*)response->data.data(), request->params[1]);
}

void Cuda::DispatchCuCtxCreate(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = sizeof(CUcontext);
  response->data.resize(response->header.size);
  response->header.result = cuCtxCreate((CUcontext*)response->data.data(), (unsigned int)request->params[1], (CUdevice)request->params[2]);
}

void Cuda::DispatchCuCtxDestroy(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuCtxDestroy((CUcontext)request->params[0]);
}

void Cuda::DispatchCuCtxPushCurrent(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuCtxPushCurrent((CUcontext)request->params[0]);
}

void Cuda::DispatchCuCtxPopCurrent(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = sizeof(CUcontext);
  response->data.resize(response->header.size);
  response->header.result = cuCtxPopCurrent((CUcontext*)response->data.data());
}

void Cuda::DispatchCuCtxSetCurrent(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuCtxSetCurrent((CUcontext)request->params[0]);
}

void Cuda::DispatchCuMemGetInfo(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = sizeof(size_t) * 2;
  response->data.resize(response->header.size);

  auto ret = (size_t*)response->data.data();
  response->header.result = cuMemGetInfo(&ret[0], &ret[1]);
}

void Cuda::TranslateJitOptions(uint32_t num_option, CUjit_option* options, void** values) {
  for (size_t i = 0; i < num_option; i++) {
    switch (options[i]) {
    case CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES:
      log_buffer_.resize((uint64_t)values[i], '\0');
      break;
    case CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES:
      error_buffer_.resize((uint64_t)values[i], '\0');
      break;
    default:
      break;
    }
  }

  for (size_t i = 0; i < num_option; i++) {
    CL_LOG("option=%d value=0x%lx", options[i], values[i]);
    switch (options[i]) {
      case CU_JIT_INFO_LOG_BUFFER:
        values[i] = (void*)log_buffer_.data();
        break;
      case CU_JIT_ERROR_LOG_BUFFER:
        values[i] = (void*)error_buffer_.data();
        break;
      case CU_JIT_THREADS_PER_BLOCK:
      case CU_JIT_MAX_REGISTERS:
      case CU_JIT_LOG_VERBOSE:
      case CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES:
      case CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES:
      case CU_JIT_TARGET:
        break;
      default:
        CL_PANIC("unimplement jit option=%d value=0x%llx", options[i], values[i]);
        break;
    }
  }
}

void Cuda::DispatchCuLinkCreate(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 4);
  response->header.size = sizeof(CUlinkState);
  response->data.resize(response->header.size);

  CUjit_option* options = nullptr;
  void** values = nullptr;
  auto num_option = (unsigned int)request->params[0];
  if (num_option > 0) {
    options = (CUjit_option*)CUDA_REQUEST_EXTEND(request);
    values = (void**)((char*)options + num_option * sizeof(CUjit_option));
    TranslateJitOptions(num_option, options, values);
  }
  response->header.result = cuLinkCreate(num_option, options, values, (CUlinkState*)response->data.data());
}

void Cuda::DispatchCuLinkAddData(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 8);
  response->header.size = 0;

  CUjit_option* options = nullptr;
  void** values = nullptr;
  const char* name = nullptr;
  auto data_size = request->params[3];
  auto num_option = (unsigned int)request->params[5];
  auto data = (void*)CUDA_REQUEST_EXTEND(request);

  if (num_option > 0) {
    options = (CUjit_option*)((char*)data + data_size);
    values = (void**)((char*)options + num_option * sizeof(CUjit_option));
    TranslateJitOptions(num_option, options, values);
  }

  if (request->params[4]) {
    if (num_option > 0) {
      name = (const char*)((char*)values + num_option * sizeof(void*));
    } else {
      name = (const char*)((char*)data + data_size);
    }
  }

  response->header.result = cuLinkAddData((CUlinkState)request->params[0], (CUjitInputType)request->params[1], 
    data, data_size, name, num_option, options, values);
}

void Cuda::DispatchCuLinkComplete(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = sizeof(void*) + sizeof(size_t);
  response->data.resize(response->header.size);

  void** bin = (void**)response->data.data();
  size_t* size = (size_t*)FIELD_OFFSET(bin);
  response->header.result = cuLinkComplete((CUlinkState)request->params[0], bin, size);
}

void Cuda::DispatchCuModuleLoadData(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = sizeof(CUmodule);
  response->data.resize(response->header.size);
  response->header.result = cuModuleLoadData((CUmodule*)response->data.data(), (const void *)request->params[1]);
}

void Cuda::DispatchCuLinkDestroy(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuLinkDestroy((CUlinkState)request->params[0]);
}

void Cuda::DispatchCuModuleGetGlobal(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 4);
  response->header.size = sizeof(CUdeviceptr) + sizeof(size_t);
  response->data.resize(response->header.size);

  const char* name = nullptr;
  if (request->params[3]) {
    name = (const char*)CUDA_REQUEST_EXTEND(request);
  }

  auto device = (CUdeviceptr*)response->data.data();
  size_t* bytes = nullptr;
  if (request->params[1]) {
    bytes = (size_t*)FIELD_OFFSET(device);
  } else {
    response->header.size -= sizeof(size_t);
  }
  response->header.result = cuModuleGetGlobal(device, bytes, (CUmodule)request->params[2], name);
}

void Cuda::DispatchCuModuleUnload(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuModuleUnload((CUmodule)request->params[0]);
}

void Cuda::DispatchCuModuleGetTexRef(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = sizeof(CUtexref);
  response->data.resize(response->header.size);

  auto name = (const char*)CUDA_REQUEST_EXTEND(request);
  response->header.result = cuModuleGetTexRef((CUtexref*)response->data.data(), (CUmodule)request->params[1], name);
}

void Cuda::DispatchCuModuleGetFunction(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = sizeof(CUfunction);
  response->data.resize(response->header.size);

  auto name = (const char*)CUDA_REQUEST_EXTEND(request);
  response->header.result = cuModuleGetFunction((CUfunction*)response->data.data(), (CUmodule)request->params[1], name);
}

void Cuda::DispatchCuFuncSetCacheConfig(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = 0;
  response->header.result = cuFuncSetCacheConfig((CUfunction)request->params[0], (CUfunc_cache)request->params[1]);
}

void Cuda::DispatchCuFuncGetAttribute(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = sizeof(int);
  response->data.resize(response->header.size);
  response->header.result = cuFuncGetAttribute((int*)response->data.data(), 
    (CUfunction_attribute)request->params[1], (CUfunction)request->params[2]);
}

void Cuda::DispatchCuMemHostAlloc(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = sizeof(void*);
  response->data.resize(response->header.size);
  response->header.result = cuMemHostAlloc((void**)response->data.data(), (size_t)request->params[1], (unsigned int)request->params[2]);
  CL_LOG("alloc host=%p", *(void**)response->data.data());
}

void Cuda::DispatchCuMemFreeHost(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuMemFreeHost((void*)request->params[0]);
  CL_LOG("free host=%p", request->params[0]);
}

void Cuda::DispatchCuMemHostGetDevicePointer(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = sizeof(CUdeviceptr);
  response->data.resize(response->header.size);

  auto host = (void*)request->params[1];
  auto iter = guest_host_memory_.find(host);
  if (iter != guest_host_memory_.end()) {
    host = iter->second;
  }
  response->header.result = cuMemHostGetDevicePointer((CUdeviceptr*)response->data.data(), host, (unsigned int)request->params[2]);
  CL_LOG("get cudev=%p host=%p", *(CUdeviceptr*)response->data.data(), (void*)request->params[1]);
}

void Cuda::DispatchCuMemHostRegister(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = sizeof(void*);
  response->data.resize(response->header.size);

  auto guest = (void*)request->params[0];
  auto size = (size_t)request->params[1];
  auto host = new uint8_t[size];
  CL_ASSERT(host != nullptr);

  response->header.result = cuMemHostRegister(host, size, (unsigned int)request->params[2]);
  CL_ASSERT(response->header.result == CUDA_SUCCESS);

  guest_host_memory_[guest] = host;
  CL_LOG("register memory host=0x%lx guest=0x%lx", host, guest);
}

void Cuda::DispatchCuMemHostUnregister(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;

  auto guest = (void*)request->params[0];
  auto host = guest_host_memory_[guest];

  response->header.result = cuMemHostUnregister(host);
  CL_ASSERT(response->header.result == CUDA_SUCCESS);
  delete (uint8_t*)host;

  guest_host_memory_.erase(guest);
  CL_LOG("unregister memory host=0x%lx guest=0x%lx", host, guest);
}

void Cuda::DispatchCuMemcpyHtoD(CudaRequest* request, RenderResponse* response) {
  response->header.size = 0;
  if (request->param_count == 3) {
    response->header.result = cuMemcpyHtoD((CUdeviceptr)request->params[0], CUDA_REQUEST_EXTEND(request), (size_t)request->params[2]);
  } else if (request->param_count == 4) {
    response->header.result = cuMemcpyHtoDAsync((CUdeviceptr)request->params[0], 
      CUDA_REQUEST_EXTEND(request), (size_t)request->params[2], (CUstream)request->params[3]);
    cuStreamSynchronize((CUstream)request->params[3]);
  } else {
    CL_PANIC("invalid requst param_count=%d", request->param_count);
  }
}

void Cuda::DispatchCuMemcpyDtoH(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = (uint32_t)request->params[2];
  response->data.resize(response->header.size);
  response->header.result = cuMemcpyDtoH((void*)response->data.data(), (CUdeviceptr)request->params[1], (size_t)request->params[2]);
}

void Cuda::DispatchCuMemAlloc(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = sizeof(CUdeviceptr);
  response->data.resize(response->header.size);
  response->header.result = cuMemAlloc((CUdeviceptr*)response->data.data(), (size_t)request->params[1]);
}

void Cuda::DispatchCuMemAllocPitch(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 5);
  response->header.size = sizeof(CUdeviceptr) + sizeof(size_t);
  response->data.resize(response->header.size);

  auto ret = (uint64_t*)response->data.data();
  response->header.result = cuMemAllocPitch((CUdeviceptr*)&ret[0], (size_t*)&ret[1], 
    (size_t)request->params[2], (size_t)request->params[3], (unsigned int)request->params[4]);
}

void Cuda::DispatchCuEventCreate(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = sizeof(CUevent);
  response->data.resize(response->header.size);
  response->header.result = cuEventCreate((CUevent*)response->data.data(), (unsigned int)request->params[1]);
}

void Cuda::DispatchCuEventRecord(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = 0;
  response->header.result = cuEventRecord((CUevent)request->params[0], (CUstream)request->params[1]);
}

void Cuda::DispatchCuEventSynchronize(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuEventSynchronize((CUevent)request->params[0]);
}

void Cuda::DispatchCuEventDestroy(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuEventDestroy((CUevent)request->params[0]);
}

void Cuda::DispatchCuLaunchKernel(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 11);
  response->header.size = 0;

  if (request->params[10]) {
    CL_PANIC("extra param was not implemented");
  }

  void** kernel_params = nullptr;
  uint64_t *guest_kernel_param_values = nullptr;
  if (request->params[9]) {
    // get kernel params count for this kernel function
    auto kernel_param_count = (size_t*)CUDA_REQUEST_EXTEND(request);
    
    // get kernel params and values from guest
    kernel_params = (void**)FIELD_OFFSET(kernel_param_count);
    auto kernel_param_values = (char*)kernel_params + (*kernel_param_count) * sizeof(void*);
    
    // copy guest kernel param value to host
    auto pos = kernel_param_values;
    guest_kernel_param_values = new uint64_t[*kernel_param_count]();
    for (size_t i = 0; i < *kernel_param_count; i++)  {
      auto size = *(size_t*)pos;
      pos += sizeof(size_t);

      // replace guest pointer in the kernel_params with host pointer
      if (size > 0) {
        memcpy(&guest_kernel_param_values[i], pos, size);
        kernel_params[i] = &guest_kernel_param_values[i];
        pos += size;
      }
      CL_LOG("value=0x%lx", guest_kernel_param_values[i]);
    }
  }

  response->header.result = cuLaunchKernel((CUfunction)request->params[0], 
    (unsigned int)request->params[1], (unsigned int)request->params[2], (unsigned int)request->params[3], 
    (unsigned int)request->params[4], (unsigned int)request->params[5], (unsigned int)request->params[6], 
    (unsigned int)request->params[7], (CUstream)request->params[8], kernel_params, nullptr);
  cuStreamSynchronize((CUstream)request->params[8]);

  if (guest_kernel_param_values != nullptr) {
    delete guest_kernel_param_values;
  }
}

void Cuda::DispatchCuStreamSynchronize(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuStreamSynchronize((CUstream)request->params[0]);
}

void Cuda::DispatchCuMemcpyDtoD(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = 0;
  response->header.result = cuMemcpyDtoD((CUdeviceptr)request->params[0], (CUdeviceptr)request->params[1], (size_t)request->params[2]);
}

void Cuda::DispatchCuMemFree(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuMemFree((CUdeviceptr)request->params[0]);
}

void Cuda::DispatchCuTexRefSetFormat(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = 0;
  response->header.result = cuTexRefSetFormat((CUtexref)request->params[0], (CUarray_format)request->params[1], (int)request->params[2]);
}

void Cuda::DispatchcuTexRefSetAddressMode(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = 0;
  response->header.result = cuTexRefSetAddressMode((CUtexref)request->params[0], (int)request->params[1], (CUaddress_mode)request->params[2]);
}

void Cuda::DispatchCuTexRefSetFilterMode(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = 0;
  response->header.result = cuTexRefSetFilterMode((CUtexref)request->params[0], (CUfilter_mode)request->params[1]);
}

void Cuda::DispatchCuTexRefSetFlags(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = 0;
  response->header.result = cuTexRefSetFlags((CUtexref)request->params[0], (unsigned int)request->params[1]);
}

void Cuda::DispatchCuTexObjectCreate(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 4);
  response->header.size = sizeof(CUtexObject);
  response->data.resize(response->header.size);

  CUDA_RESOURCE_DESC* res_desc = nullptr;
  CUDA_TEXTURE_DESC* tex_desc = nullptr;
  CUDA_RESOURCE_VIEW_DESC* view_desc = nullptr;
  if (request->params[1]) {
    res_desc = (CUDA_RESOURCE_DESC*)CUDA_REQUEST_EXTEND(request);
  }
  if (request->params[2]) {
    tex_desc = (CUDA_TEXTURE_DESC*)FIELD_OFFSET(res_desc);
  }
  if (request->params[3]) {
    view_desc = (CUDA_RESOURCE_VIEW_DESC*)FIELD_OFFSET(tex_desc);
  }
  response->header.result = cuTexObjectCreate((CUtexObject*)response->data.data(), res_desc, tex_desc, view_desc);
}

void Cuda::DispatchCuTexObjectDestroy(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuTexObjectDestroy((CUtexObject)request->params[0]);
}

void Cuda::DispatchCuTexRefSetArray(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 3);
  response->header.size = 0;
  response->header.result = cuTexRefSetArray((CUtexref)request->params[0], (CUarray)request->params[1], (unsigned int)request->params[2]);
}

void Cuda::DispatchCuTexRefSetAddress(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 4);
  if (request->params[0]) {
    response->header.size = sizeof(size_t);
    response->data.resize(response->header.size);
    response->header.result = cuTexRefSetAddress((size_t*)response->data.data(), (CUtexref)request->params[1], 
      (CUdeviceptr)request->params[2], (size_t)request->params[3]);
  } else {
    response->header.size = 0;
    response->header.result = cuTexRefSetAddress(nullptr, (CUtexref)request->params[1], 
      (CUdeviceptr)request->params[2], (size_t)request->params[3]);
  }
}

void Cuda::DispatchCuArrayCreate(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = sizeof(CUarray);
  response->data.resize(response->header.size);
  response->header.result = cuArrayCreate((CUarray*)response->data.data(), (CUDA_ARRAY_DESCRIPTOR*)CUDA_REQUEST_EXTEND(request));
}

void Cuda::DispatchCuArrayDestroy(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  response->header.size = 0;
  response->header.result = cuArrayDestroy((CUarray)request->params[0]);
}

void Cuda::DispatchCuMemcpy2D(CudaRequest* request, RenderResponse* response) {
  auto copy = (CUDA_MEMCPY2D*)CUDA_REQUEST_EXTEND(request);

  std::string data_copy;
  if (copy->srcMemoryType == CU_MEMORYTYPE_HOST) {
    CL_ASSERT(copy->dstMemoryType != CU_MEMORYTYPE_HOST); 
    response->header.size = 0;
    auto data = FIELD_OFFSET(copy);
    if (copy->srcPitch == copy->WidthInBytes) {
      copy->srcHost = data;
    } else {
      // align data with pitch
      data_copy.resize(copy->srcPitch * copy->Height);
      for (size_t h = 0; h < copy->Height; h++) {
        memcpy((char*)data_copy.data() + h * copy->srcPitch, data + h * copy->WidthInBytes, copy->WidthInBytes);
      }
      copy->srcHost = data_copy.data();
    }
  } else if (copy->dstMemoryType == CU_MEMORYTYPE_HOST) {
    CL_ASSERT(copy->srcMemoryType != CU_MEMORYTYPE_HOST);
    response->header.size = copy->WidthInBytes * copy->Height;
    response->data.resize(response->header.size);
    if (copy->dstPitch == copy->WidthInBytes) { 
      copy->dstHost = (void*)response->data.data();
    } else {
      data_copy.resize(copy->dstPitch * copy->Height);
      copy->dstHost = (void*)data_copy.data();
    }
  }

  if (request->param_count == 1) {
    response->header.result = cuMemcpy2D(copy);
  } else if (request->param_count == 2) {
    response->header.result = cuMemcpy2DAsync(copy, (CUstream)request->params[1]);
    cuStreamSynchronize((CUstream)request->params[1]);
  } else {
    CL_PANIC("invalid requst param_count=%d", request->param_count);
  }

  // only copy valid data to guest by WidthInBytes in each line
  if (response->header.result == CUDA_SUCCESS 
    && copy->dstMemoryType == CU_MEMORYTYPE_HOST 
    && copy->dstPitch != copy->WidthInBytes) {
    for (size_t h = 0; h < copy->Height; h++) {
      memcpy((char*)response->data.data() + h * copy->WidthInBytes, data_copy.data() + h * copy->dstPitch, copy->WidthInBytes);
    }
  }
}

void Cuda::DispatchCuMemcpy3D(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 1);
  auto copy = (CUDA_MEMCPY3D*)CUDA_REQUEST_EXTEND(request);

  std::string data_copy;
  if (copy->srcMemoryType == CU_MEMORYTYPE_HOST) {
    CL_ASSERT(copy->dstMemoryType != CU_MEMORYTYPE_HOST); 
    response->header.size = 0;
    auto data = FIELD_OFFSET(copy);
    if (copy->srcPitch == copy->WidthInBytes) {
      copy->srcHost = data;
    } else {
      // align data with pitch
      data_copy.resize(copy->srcPitch * copy->Height * copy->Depth);
      for (size_t z = 0; z < copy->Depth; z++) {
        for (size_t h = 0; h < copy->Height; h++) {
          memcpy((char*)data_copy.data() + z * h * copy->srcPitch + h * copy->srcPitch, 
            data + z * h * copy->WidthInBytes + h * copy->WidthInBytes,
            copy->WidthInBytes);
        }
      }
      copy->srcHost = data_copy.data();
    }
  } else if (copy->dstMemoryType == CU_MEMORYTYPE_HOST) {
    CL_ASSERT(copy->srcMemoryType != CU_MEMORYTYPE_HOST);
    response->header.size = copy->WidthInBytes * copy->Height * copy->Depth;
    response->data.resize(response->header.size);
    if (copy->dstPitch == copy->WidthInBytes) {
      copy->dstHost = (void*)response->data.data();
    } else {
      data_copy.resize(copy->dstPitch * copy->Height * copy->Depth);
      copy->dstHost = (void*)data_copy.data();
    }
  }

  if (request->param_count == 1) {
    response->header.result = cuMemcpy3D(copy);
  } else if (request->param_count == 2) {
    response->header.result = cuMemcpy3DAsync(copy, (CUstream)request->params[1]);
    cuStreamSynchronize((CUstream)request->params[1]);
  } else {
    CL_PANIC("invalid requst param_count=%d", request->param_count);
  }

  // only copy valid data to guest by WidthInBytes in each line
  if (response->header.result == CUDA_SUCCESS 
    && copy->dstMemoryType == CU_MEMORYTYPE_HOST 
    && copy->dstPitch != copy->WidthInBytes) {
    for (size_t z = 0; z < copy->Depth; z++) {
      for (size_t h = 0; h < copy->Height; h++) {
        memcpy((char*)response->data.data() + z * h * copy->WidthInBytes + h * copy->WidthInBytes, 
          data_copy.data() + z * h * copy->dstPitch + h * copy->dstPitch,
          copy->WidthInBytes);
      }
    }
  }
}

void Cuda::DispatchCuArray3DCreate(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = sizeof(CUarray);
  response->data.resize(response->header.size);
  response->header.result = cuArray3DCreate((CUarray*)response->data.data(), (CUDA_ARRAY3D_DESCRIPTOR*)CUDA_REQUEST_EXTEND(request));
}

void Cuda::DispatchCuStreamCreate(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 2);
  response->header.size = sizeof(CUstream);
  response->data.resize(response->header.size);
  response->header.result = cuStreamCreate((CUstream*)response->data.data(), (unsigned int)request->params[1]);
}

void Cuda::DispatchCuMemsetD8Async(CudaRequest* request, RenderResponse* response) {
  CL_ASSERT(request->param_count == 4);
  response->header.size = 0;
  response->header.result = cuMemsetD8Async((CUdeviceptr)request->params[0], (unsigned char)request->params[1], 
    (size_t)request->params[2], (CUstream)request->params[3]);
  cuStreamSynchronize((CUstream)request->params[3]);
}

void Cuda::Dispatch(WorkerItem* item) {
  auto request = (CudaRequest*)item->request.data.data();
  CL_LOG("call api=%s param_count=%d", GetCudaFunctionName(request->api_index), request->param_count);
  
  CL_ASSERT(request->version == version_);
  Render::Dispatch(item);

  switch (request->api_index) {
    case CUINIT:
      DispatchCuInit(request, &item->response);
      break;
    case CUDRIVERGETVERSION:
      DispatchCuDriverGetVersion(request, &item->response);
      break;
    case CUDEVICEGETCOUNT:
      DispatchCuDeviceGetCount(request, &item->response);
      break;
    case CUDEVICEGET:
      DispatchCuDeviceGet(request, &item->response);
      break;
    case CUDEVICEGETNAME:
      DispatchCuDeviceGetName(request, &item->response);
      break;
    case CUDEVICEGETUUID:
      DispatchCuDeviceGetUuid(request, &item->response);
      break;
    case CUDEVICETOTALMEM:
      DispatchCuDeviceTotalMem(request, &item->response);
      break;
    case CUDEVICEGETATTRIBUTE:
      DispatchCuDeviceGetAttribute(request, &item->response);
      break;
    case CUDEVICECOMPUTECAPABILITY:
      DispatchCuDeviceComputeCapability(request, &item->response);
      break;
    case CUCTXCREATE:
      DispatchCuCtxCreate(request, &item->response);
      break;
    case CUCTXDESTROY:
      DispatchCuCtxDestroy(request, &item->response);
      break;
    case CUCTXPUSHCURRENT:
      DispatchCuCtxPushCurrent(request, &item->response);
      break;
    case CUCTXPOPCURRENT:
      DispatchCuCtxPopCurrent(request, &item->response);
      break;
    case CUCTXSETCURRENT:
      DispatchCuCtxSetCurrent(request, &item->response);
      break; 
    case CUMODULELOADDATA:
      DispatchCuModuleLoadData(request, &item->response);
      break;
    case CUMODULEUNLOAD:
      DispatchCuModuleUnload(request, &item->response);
      break;
    case CUMODULEGETFUNCTION:
      DispatchCuModuleGetFunction(request, &item->response);
      break;
    case CUMODULEGETGLOBAL:
      DispatchCuModuleGetGlobal(request, &item->response);
      break;
    case CULINKCREATE:
      DispatchCuLinkCreate(request, &item->response);
      break;
    case CULINKADDDATA:
      DispatchCuLinkAddData(request, &item->response);
      break;
    case CULINKCOMPLETE:
      DispatchCuLinkComplete(request, &item->response);
      break;
    case CULINKDESTROY:
      DispatchCuLinkDestroy(request, &item->response);
      break;
    case CUMODULEGETTEXREF:
      DispatchCuModuleGetTexRef(request, &item->response);
      break;
    case CUMEMGETINFO:
      DispatchCuMemGetInfo(request, &item->response);
      break;
    case CUMEMALLOC:
      DispatchCuMemAlloc(request, &item->response);
      break;
    case CUMEMALLOCPITCH:
      DispatchCuMemAllocPitch(request, &item->response);
      break;
    case CUMEMFREE:
      DispatchCuMemFree(request, &item->response);
      break;
    case CUMEMHOSTALLOC:
      DispatchCuMemHostAlloc(request, &item->response);
      break;
    case CUMEMFREEHOST:
      DispatchCuMemFreeHost(request, &item->response);
      break;
    case CUMEMHOSTGETDEVICEPOINTER:
      DispatchCuMemHostGetDevicePointer(request, &item->response);
      break;
    case CUMEMHOSTREGISTER:
      DispatchCuMemHostRegister(request, &item->response);
      break;
    case CUMEMHOSTUNREGISTER:
      DispatchCuMemHostUnregister(request, &item->response);
      break;
    case CUMEMCPYHTOD:
    case CUMEMCPYHTODASYNC:
      DispatchCuMemcpyHtoD(request, &item->response);
      break;
    case CUMEMCPYDTOH:
      DispatchCuMemcpyDtoH(request, &item->response);
      break;
    case CUMEMCPYDTOD:
      DispatchCuMemcpyDtoD(request, &item->response);
      break;
    case CUMEMCPY2D:
    case CUMEMCPY2DASYNC:
      DispatchCuMemcpy2D(request, &item->response);
      break;
    case CUMEMCPY3D:
    case CUMEMCPY3DASYNC:
      DispatchCuMemcpy3D(request, &item->response);
      break;
    case CUMEMSETD8ASYNC:
      DispatchCuMemsetD8Async(request, &item->response);
      break; 
    case CUARRAYCREATE:
      DispatchCuArrayCreate(request, &item->response);
      break;
    case CUARRAYDESTROY:
      DispatchCuArrayDestroy(request, &item->response);
      break;
    case CUARRAY3DCREATE:
      DispatchCuArray3DCreate(request, &item->response);
      break;
    case CUSTREAMCREATE:
      DispatchCuStreamCreate(request, &item->response);
      break;
    case CUEVENTCREATE:
      DispatchCuEventCreate(request, &item->response);
      break;
    case CUEVENTRECORD:
      DispatchCuEventRecord(request, &item->response);
      break;
    case CUEVENTSYNCHRONIZE:
      DispatchCuEventSynchronize(request, &item->response);
      break;
    case CUEVENTDESTROY:
      DispatchCuEventDestroy(request, &item->response);
      break;  
    case CUFUNCSETCACHECONFIG:
      DispatchCuFuncSetCacheConfig(request, &item->response);
      break;
    case CUFUNCGETATTRIBUTE:
      DispatchCuFuncGetAttribute(request, &item->response);
      break;
    case CULAUNCHKERNEL:
      DispatchCuLaunchKernel(request, &item->response);
      break;
    case CUSTREAMSYNCHRONIZE:
      DispatchCuStreamSynchronize(request, &item->response);
      break;
    case CUTEXREFSETARRAY:
      DispatchCuTexRefSetArray(request, &item->response);
      break;  
    case CUTEXREFSETADDRESS:
      DispatchCuTexRefSetAddress(request, &item->response);
      break;
    case CUTEXREFSETFORMAT:
      DispatchCuTexRefSetFormat(request, &item->response);
      break;
    case CUTEXREFSETADDRESSMODE:
      DispatchcuTexRefSetAddressMode(request, &item->response);
      break;
    case CUTEXREFSETFILTERMODE:
      DispatchCuTexRefSetFilterMode(request, &item->response);
      break;
    case CUTEXREFSETFLAGS:
      DispatchCuTexRefSetFlags(request, &item->response);
      break;
    case CUTEXOBJECTCREATE:
      DispatchCuTexObjectCreate(request, &item->response);
      break;
    case CUTEXOBJECTDESTROY:
      DispatchCuTexObjectDestroy(request, &item->response);
      break;
    default:
      CL_PANIC("api=%s not implement", GetCudaFunctionName(request->api_index));
      break;
  }

  if (item->response.header.result != CUDA_SUCCESS) {
    CL_PANIC("handle api=%s result=%d failed", GetCudaFunctionName(request->api_index), item->response.header.result);
    return;
  }
}
