/* 
 * Clink
 * Copyright (C) 2023 cair <rui.cai@tenclass.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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