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