#include "tcp.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include "logger.h"

Tcp::Tcp(boost::asio::io_context& io_context, uuid_t uuid) : Socket(uuid), socket_(io_context), acceptor_(io_context) {
}

Tcp::~Tcp() {
  if (acceptor_.is_open()) {
    acceptor_.close();
  }

  if (socket_.is_open()) {
    boost::system::error_code ignore_err;
    socket_.shutdown(socket_.shutdown_both, ignore_err);
    socket_.close();
  }
}

bool Tcp::Accept(uint16_t port) {
  try {
    // bind port to listen
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    // wait for client
    acceptor_.accept(socket_);
    // close server socket
    acceptor_.close();

    // set socket options
    boost::asio::socket_base::send_buffer_size send_size_option(SOCKET_BUFFER_SIZE);
	  socket_.set_option(send_size_option);

    boost::asio::socket_base::receive_buffer_size recv_size_option(SOCKET_BUFFER_SIZE);
	  socket_.set_option(recv_size_option);

    socket_.set_option(boost::asio::ip::tcp::no_delay(true));
    socket_.set_option(boost::asio::socket_base::keep_alive(true));
    return true;
  } catch (const std::exception& e) {
    CL_ERROR("exception=%s", e.what());
    return false;
  }
}

bool Tcp::Read(void* data, size_t size) {
  try {
    size_t bytes_return = boost::asio::read(socket_, boost::asio::buffer(data, size));
    if (bytes_return != size) {
      CL_ERROR("read bytes error bytes_return=%lld size=%lld", bytes_return, size);
      return false;
    }
    return true;
  } catch (const std::exception& e) {
    CL_ERROR("exception=%s", e.what());
    return false;
  }
}

bool Tcp::Write(void* data, size_t size) {
  try {
    size_t bytes_return = boost::asio::write(socket_, boost::asio::buffer(data, size));
    if (bytes_return != size) {
      CL_ERROR("write bytes error bytes_return=%lld size=%lld", bytes_return, size);
      return false;
    }
    return true;
  } catch (const std::exception& e) {
    CL_ERROR("exception=%s", e.what());
    return false;
  }
}
