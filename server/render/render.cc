#include "render.h"
#include "logger.h"
#include "utilities.h"

Render::Render() {
  finalized_ = false;
  worker_thread_ = std::thread(&Render::Consumer, this);
}

Render::~Render() {
  finalized_ = true;

  if (worker_thread_.joinable()) {
    worker_cv_.notify_all();
    worker_thread_.join();
  }
}

void Render::Dispatch(WorkerItem* item) {
  item->response.header.pid = pid_;
  item->response.header.tid = tid_;
  item->response.header.decompress = NO_COMPRESS;
}

void Render::Consumer() {
  auto name = "cuda-" + std::to_string(tid_);
  SetThreadName(name.c_str());

  RenderResponse response;
  while (!finalized_) {
    std::unique_lock<std::mutex> lock(worker_mutex_);
    worker_cv_.wait(lock, [this]() { 
      return !worker_queue_.empty() || finalized_; 
    });

    if (finalized_) {
      break;
    }

    auto item = worker_queue_.front();
    // unlock queue immediately to make producer faster
    lock.unlock();

    // consume it
    Dispatch(item);
    item->finish();

    /* Only remove item after job is done.
     * Remember to lock mutex again when operating on worker_queue_
     */
    lock.lock();
    worker_queue_.pop();
  }
}

void Render::Producer(WorkerItem* item) {
  worker_mutex_.lock();
  worker_queue_.push(item);
  worker_mutex_.unlock();
  worker_cv_.notify_all();
}