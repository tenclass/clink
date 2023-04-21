#pragma once

#include "ikcp.h"
#include "socket.h"
#include <mutex>
#include <thread>
#include <condition_variable>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>

class Kcp : public Socket {
public:
  Kcp(boost::asio::io_context& io_context);
  ~Kcp();

  virtual bool Connect(std::string host, std::string port);
  virtual bool Read(void* data, size_t size);
  virtual bool Write(void* data, size_t size);

  boost::asio::ip::udp::socket& socket() { return socket_; }

private:
  ikcpcb* ikcp_ = nullptr;
  bool finalized_;
  int max_frame_size_ = 0;
  std::thread recv_thread_;
  std::thread update_timer_;
  std::mutex mutex_;
  std::condition_variable cv_;

  boost::asio::ip::udp::socket socket_;
};
