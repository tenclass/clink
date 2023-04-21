#include "kcp.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <chrono>
#include <uuid/uuid.h>
#include "utilities.h"
#include "logger.h"

static int kcp_output(const char* buf, int len, ikcpcb* kcp, void* user) {
  CL_UNUSED(kcp);
  auto kcp_socket = (Kcp*)user;
  boost::system::error_code error;
  auto ret = kcp_socket->socket().send_to(boost::asio::buffer(buf, len), kcp_socket->remote_endpoint(), 0, error);
  if (error) {
    CL_ERROR("send data error=%s", error.what().c_str());
    return -1;
  }
  return ret;
}

Kcp::Kcp(boost::asio::io_context& io_context, uuid_t uuid) : Socket(uuid), socket_(io_context) {
  finalized_ = false;
}

Kcp::~Kcp() {
  finalized_ = true;

  if (socket_.is_open()) {
    boost::system::error_code ignore_err;
    socket_.shutdown(socket_.shutdown_both, ignore_err);
    socket_.close();
  }

  if (update_timer_.joinable()) {
    update_timer_.join();
  }
  if (recv_thread_.joinable()) {
    recv_thread_.join();
  }

  cv_.notify_all();
  ikcp_release(kcp_);
}

bool Kcp::Accept(uint16_t port) {
  boost::system::error_code error;
  socket_.open(boost::asio::ip::udp::v4(), error);
  if (error) {
    CL_ERROR("failed to open socket");
    return false;
  }

  socket_.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port), error);
  if (error) {
    CL_ERROR("failed to bind port=%d error=%s", port, error.what().c_str());
    return false;
  }

  boost::asio::socket_base::send_buffer_size send_size_option(SOCKET_BUFFER_SIZE);
  socket_.set_option(send_size_option, error);
  if (error) {
    CL_ERROR("failed to set option");
    return false;
  }

  boost::asio::socket_base::receive_buffer_size recv_size_option(SOCKET_BUFFER_SIZE);
  socket_.set_option(recv_size_option, error);
  if (error) {
    CL_ERROR("failed to set option");
    return false;
  }

  char uuid_string[100];
  uuid_unparse(uuid_, uuid_string);
  CL_LOG("kcp server uuid=%s", uuid_string);

  kcp_ = ikcp_create(1, this);
  ikcp_setoutput(kcp_, kcp_output);
  ikcp_nodelay(kcp_, 2, 10, 2, 1);
  ikcp_wndsize(kcp_, 128, 128);
  //ikcp_setmtu(kcp_, 1024);
  kcp_->fastresend = 1;
  kcp_->interval = 1;
  kcp_->rx_minrto = 1;
  max_frame_size_ = kcp_->mss * (kcp_->rcv_wnd - 1);

  update_timer_ = std::thread([this]() {
    CL_LOG("kcp update loop start");
    IUINT32 now, time_sleep = 10;
    auto time_base = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    while (!finalized_) {
      std::this_thread::sleep_for(std::chrono::milliseconds(time_sleep));
      now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - time_base;
      mutex_.lock();
      ikcp_update(kcp_, now);
      time_sleep = ikcp_check(kcp_, now) - now;
      mutex_.unlock();
    }
    CL_LOG("kcp update loop end");
  });

  recv_thread_ = std::thread([this]() {
    CL_LOG("kcp recv loop start");
    ssize_t recv_len;
    boost::system::error_code error;
    auto buffer = new char[SOCKET_BUFFER_SIZE];
    while (!finalized_) {
      recv_len = socket_.receive_from(boost::asio::buffer(buffer, SOCKET_BUFFER_SIZE), remote_endpoint_, 0, error);
      if (error) {
        CL_ERROR("receive from socket erro=%s", error.what().c_str());
        break;
      }

      if (recv_len > 0) {
        mutex_.lock();
        ikcp_input(kcp_, buffer, recv_len);
        mutex_.unlock();
        cv_.notify_all();
      }
    }
    delete buffer;
    CL_LOG("kcp recv loop end");
  });
  return true;
}

bool Kcp::Read(void* data, size_t size) {
  int recv_size, peek_size;
  auto remain = size;
  auto pos = (char*)data;
  while (remain > 0 && !finalized_) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this, &peek_size]() { 
      peek_size = ikcp_peeksize(kcp_);
      return peek_size > 0 || finalized_;
    });

    if (finalized_) {
      return false;
    }

    recv_size = ikcp_recv(kcp_, (char*)pos, peek_size);
    pos += recv_size;
    remain -= recv_size;
  }
  return true;
}

bool Kcp::Write(void* data, size_t size) {
  int send_size;
  auto remain = size;
  auto pos = (char*)data;
  std::lock_guard<std::mutex> lock(mutex_);
  while (remain > 0) {
    send_size = std::min((int)remain, max_frame_size_);
    if (ikcp_send(kcp_, pos, send_size) < 0) {
      CL_ERROR("kcp write err");
      return false;
    }

    pos += send_size;
    remain -= send_size;
    ikcp_flush(kcp_);
  }
  return true;
}
