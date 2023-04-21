#ifndef _CLINK_TCP_H
#define _CLINK_TCP_H

#include "socket.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <uuid/uuid.h>

class Tcp : public Socket {
public:
  Tcp(boost::asio::io_context& io_context, uuid_t uuid);
  ~Tcp();

  virtual bool Accept(uint16_t port);
  virtual bool Read(void* data, size_t size);
  virtual bool Write(void* data, size_t size);

private:
  boost::asio::ip::tcp::socket socket_;
  boost::asio::ip::tcp::acceptor acceptor_;
};

#endif
