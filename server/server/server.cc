#include "server.h"
#include <cstring>
#include "logger.h"
#include "cuda.h"
#include "tcp.h"
#include "kcp.h"

Server::Server(uint16_t port, uuid_t uuid) {
  port_ = port;
  finalized_ = false;
  uuid_copy(uuid_, uuid);
}

Server::~Server() {
  finalized_ = true;

  if (response_loop_.joinable()) {
    response_cv_.notify_all();
    response_loop_.join();
  }

  if (zstd_) {
    delete zstd_;
    zstd_ = nullptr;
  }

  for (auto iter = renders_.begin(); iter != renders_.end(); iter++) {
    for (auto iter1 = iter->second.begin(); iter1 != iter->second.end(); iter1++) {
      delete iter1->second;
    }
  }
  renders_.clear();
}

void Server::RequestLoop() {
  SetThreadName("request-loop");

  bool ret = false;
  while (!finalized_) {
    WorkerItem* item = new WorkerItem;

    ret = socket_->Read(&item->request.header, sizeof(RenderRequestHeader));
    if (!ret) {
      CL_ERROR("read client data failed");
      break;
    }

    auto render = renders_[item->request.header.pid][item->request.header.tid];
    if (render == nullptr) {
      switch (item->request.header.render) {
        case RENDER_CUDA:
          render = new Cuda(CUDA_VERSION, item->request.header.pid, item->request.header.tid);
          renders_[item->request.header.pid][item->request.header.tid] = render;
          break;
        case RENDER_OPENCL:
          // not implement
        default:
          CL_PANIC("render type=%d not implement", item->request.header.render);
          break;
      }
    }

    item->request.data.resize(item->request.header.size);
    ret = socket_->Read((void*)item->request.data.data(), item->request.data.size());
    if (!ret) {
      CL_ERROR("read client data failed");
      break;
    }

    if (item->request.header.compress == ZSTD_COMPRESS_TYPE) {
      item->request.data = std::move(zstd_->Decompress(item->request.data));
    }

    item->finish = [item, this]() {
      if (!item->request.header.sync) {
        delete item;
        return;
      }

      response_mutex_.lock();
      response_queue_.emplace(item);
      response_mutex_.unlock();
      response_cv_.notify_all();
    };
    render->Producer(item);
  }
}

void Server::ResponseLoop() {
  SetThreadName("response-loop");

  bool ret = true;
  while (!finalized_) {
    std::unique_lock<std::mutex> lock(response_mutex_);
    response_cv_.wait(lock, [this]() { 
      return !response_queue_.empty() || finalized_; 
    });

    if (finalized_) {
      break;
    }
    
    auto item = response_queue_.front();
    lock.unlock();

    // compress it
    if (item->response.header.size > ZSTD_COMPRESS_DATA_MIN_SIZE) {
      item->response.data = std::move(zstd_->Compress(item->response.data));
      item->response.header.decompress = ZSTD_COMPRESS_TYPE;
      item->response.header.size = item->response.data.size();
    }

    // send it
    ret = socket_->Write(&item->response.header, sizeof(RenderResponseHeader));
    if (ret && item->response.header.size > 0) {
      ret = socket_->Write((void*)item->response.data.data(), item->response.header.size);
    }
    delete item;

    if (!ret && !finalized_) {
      CL_ERROR("write error happened");
      finalized_ = true;
    }

    lock.lock();
    response_queue_.pop();
  }
}

void Server::Run(NetworkProtocol net) {
  CL_LOG("server start");

  zstd_ = new ZSTDUtil(ZSTD_COMPRESS_WORKER_NUM, ZSTD_COMPRESS_LEVEL, ZSTD_COMPRESS_WINDOW_POWER);
  if (zstd_ == nullptr) {
    CL_ERROR("create zstd failed");
    return;
  }

  switch (net) {
  case tcp:
    socket_ = new Tcp(io_context, uuid_);
    break;
  case kcp:
    socket_ = new Kcp(io_context, uuid_);
    break;
  }
  
  if (socket_ == nullptr) {
    CL_ERROR("create socket failed");
    return;
  }

  if (!socket_->Accept(port_)) {
    CL_ERROR("accept client connection failed");
    return;
  }

  // create response loop thread to send api response
  response_loop_ = std::thread(&Server::ResponseLoop, this);

  // create request loop to handle api request
  request_loop_ = std::thread(&Server::RequestLoop, this);
  request_loop_.join();

  CL_LOG("server end");
}

void Server::Quit() {
  finalized_ = true;

  if (socket_) {
    delete socket_;
    socket_ = nullptr;
  }
}
