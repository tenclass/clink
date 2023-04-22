#include "common/global.h"
#include "kcp.h"
#include <cstring>
#include <algorithm>
#include <chrono>
#include "utilities.h"

static int kcp_output(const char* buf, int len, ikcpcb* kcp, void* user) {
  CL_UNUSED(kcp);
  boost::system::error_code error;
  auto kcp_socket = (Kcp*)user;
  auto ret = (int)kcp_socket->socket().send(boost::asio::buffer(buf, len), 0, error);
  if (error) {
    CL_ERROR("send data error=%s",error.what().c_str());
    return -1;
  }
  return ret;
}

Kcp::Kcp(boost::asio::io_context& io_context) : socket_(io_context) {
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
  if (ikcp_) {
    ikcp_release(ikcp_);
  }
}

bool Kcp::Connect(std::string host, std::string port) {
  boost::system::error_code error;
  boost::asio::ip::udp::resolver resolver(socket_.get_executor());
  boost::asio::ip::udp::resolver::results_type endpoints = resolver.resolve(host, port);
  boost::asio::connect(socket_, endpoints, error);
  if (error) {
    CL_ERROR("connect failed error=%s",error.what().c_str());
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

  auto uuid_string = std::getenv("CLINK_UUID");
  if (!uuid_string) {
    CL_ERROR("failed to get uuid from env");
    return false;
  }
  CL_LOG("kcp server uuid=%s", uuid_string);

  ikcp_ = ikcp_create(1, this);
  ikcp_setoutput(ikcp_, kcp_output);
  ikcp_nodelay(ikcp_, 2, 10, 2, 1);
  ikcp_wndsize(ikcp_, 128, 128);
  //ikcp_setmtu(ikcp_, 1024);
  ikcp_->fastresend = 1;
  ikcp_->interval = 1;
  ikcp_->rx_minrto = 1;
  max_frame_size_ = ikcp_->mss * (ikcp_->rcv_wnd - 1);

  update_timer_ = std::thread([this]() {
    CL_LOG("kcp update loop start");
    IUINT32 now, time_sleep = 10;
    auto time_base = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    while (!finalized_) {
      std::this_thread::sleep_for(std::chrono::milliseconds(time_sleep));
      now = (IUINT32)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - time_base);
      mutex_.lock();
      ikcp_update(ikcp_, now);
      time_sleep = ikcp_check(ikcp_, now) - now;
      mutex_.unlock();
    }
    CL_LOG("kcp update loop end");
  });

  recv_thread_ = std::thread([this]() {
    CL_LOG("kcp recv loop start");
    int recv_len;
    boost::system::error_code error;
    int addr_len = sizeof(sockaddr_in);
    auto buffer = new char[SOCKET_BUFFER_SIZE];
    while (!finalized_) {
      recv_len = (int)socket_.receive(boost::asio::buffer(buffer, SOCKET_BUFFER_SIZE), 0, error);
      if (error) {
        CL_ERROR("receive from socket error=%s",error.what().c_str());
        break;
      }

      if (recv_len > 0) {
        mutex_.lock();
        ikcp_input(ikcp_, buffer, recv_len);
        mutex_.unlock();
        cv_.notify_all();
      }
    }
    delete[] buffer;
    CL_LOG("kcp recv loop end");
  });
  return true;
}

bool Kcp::Read(void* data, size_t size) {
  int recv_size, peek_size;
  auto remain = size;
  auto pos = (char*)data;
  while (remain > 0) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this, &peek_size]() {
      peek_size = ikcp_peeksize(ikcp_);
      return peek_size > 0 || finalized_;
    });

    if (finalized_) {
      return false;
    }

    recv_size = ikcp_recv(ikcp_, (char*)pos, peek_size);
    pos += recv_size;
    remain -= recv_size;
  }
  return true;
}

bool Kcp::Write(void* data, size_t size) {
  int ret, send_size;
  auto remain = size;
  auto pos = (char*)data;
  std::unique_lock<std::mutex> lock(mutex_);
  while (remain > 0) {
    send_size = min((int)remain, max_frame_size_);
    ret = ikcp_send(ikcp_, pos, send_size);
    if (ret < 0) {
      CL_ERROR("kcp write err=%d send_size=%d", ret, send_size);
      return false;
    }

    pos += send_size;
    remain -= send_size;
    ikcp_flush(ikcp_);
  }
  return true;
}
