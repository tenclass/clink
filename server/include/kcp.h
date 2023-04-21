#ifndef _CLINK_KCP_H
#define _CLINK_KCP_H

#include "ikcp.h"
#include "socket.h"
#include <mutex>
#include <thread>
#include <condition_variable>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>

class Kcp : public Socket {
public:
  Kcp(boost::asio::io_context& io_context, uuid_t uuid);
  ~Kcp();

  virtual bool Accept(uint16_t port);
  virtual bool Read(void* data, size_t size);
  virtual bool Write(void* data, size_t size);

  boost::asio::ip::udp::socket& socket() {return socket_;}
  boost::asio::ip::udp::endpoint& remote_endpoint() {return remote_endpoint_;}

private:
  ikcpcb* kcp_;
  bool finalized_;
  int max_frame_size_;
  std::thread update_timer_;
  std::thread recv_thread_;
  std::mutex mutex_;
  std::condition_variable cv_;

  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint remote_endpoint_;
};

#endif
