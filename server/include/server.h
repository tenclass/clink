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

#ifndef _CLINK_SERVER_H
#define _CLINK_SERVER_H

#include <uuid/uuid.h>
#include <boost/asio/io_context.hpp>
#include <map>
#include <queue>
#include <string>
#include "render.h"
#include "socket.h"
#include "utilities.h"

enum NetworkProtocol {
  tcp,
  kcp
};

class Server {
 private:
  uint16_t port_;
  uuid_t uuid_;
  bool finalized_;
  std::thread request_loop_;
  std::thread response_loop_;
  std::mutex response_mutex_;
  std::condition_variable response_cv_;
  std::queue<WorkerItem*> response_queue_;
  std::map<uint64_t, std::map<uint64_t, Render*>> renders_;
  boost::asio::io_context io_context;
  Socket* socket_;
  ZSTDUtil* zstd_;

  void RequestLoop();
  void ResponseLoop();

 public:
  Server(uint16_t port, uuid_t uuid);
  ~Server();

  void Run(NetworkProtocol net);
  void Quit();
};

#endif