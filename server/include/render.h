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

#ifndef _CLINK_RENDER_H
#define _CLINK_RENDER_H

#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>

#define RENDER_CUDA 0
#define RENDER_OPENCL 1

struct RenderRequestHeader {
  bool sync;
  uint8_t render;
  uint8_t compress;
  uint32_t pid;
  uint32_t tid;
  uint32_t size;
} __attribute__((packed));

struct RenderResponseHeader {
  uint8_t decompress;
  uint32_t pid;
  uint32_t tid;
  uint32_t result;
  uint32_t size;
} __attribute__((packed));

struct RenderRequest {
  struct RenderRequestHeader header;
  std::string data;
};

struct RenderResponse {
  struct RenderResponseHeader header;
  std::string data;
};

typedef std::function<void(void)> RenderCallback;
struct WorkerItem {
  RenderRequest request;
  RenderResponse response;
  RenderCallback finish;
};

class Render {
private:
  bool finalized_;
  std::mutex worker_mutex_;
  std::thread worker_thread_;
  std::condition_variable worker_cv_;
  std::queue<WorkerItem*> worker_queue_;

  void Consumer();
public:
  Render();
  virtual ~Render();

  void Producer(WorkerItem* item);
  virtual void Dispatch(WorkerItem* item);

protected:
  uint32_t pid_;
  uint32_t tid_;
};

#endif
