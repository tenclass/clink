#include "../common/global.h"
#include "tcp.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>


Tcp::Tcp(boost::asio::io_context& io_context) : socket_(io_context) {

}

Tcp::~Tcp() {
  if (socket_.is_open()) {
    socket_.shutdown(socket_.shutdown_both);
    socket_.close();
  }
}

bool Tcp::Connect(std::string host, std::string port) {
  try {
    boost::asio::ip::tcp::resolver resolver(socket_.get_executor());
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, port);
    boost::asio::connect(socket_, endpoints);

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
