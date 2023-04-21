#pragma once

#include "socket.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>

class Tcp : public Socket {
public:
  Tcp(boost::asio::io_context& io_context);
  ~Tcp();

  virtual bool Connect(std::string host, std::string port);
  virtual bool Read(void* data, size_t size);
  virtual bool Write(void* data, size_t size);

private:
  boost::asio::ip::tcp::socket socket_;
};
