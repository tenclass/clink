#pragma once

#include <string>

#define SOCKET_BUFFER_SIZE 10 * 1024 * 1024

class Socket {
public:
  Socket() = default;
  virtual ~Socket () = default;

  virtual bool Connect(std::string host, std::string port) = 0;
  virtual bool Read(void* data, size_t size) = 0;
  virtual bool Write(void* data, size_t size) = 0;
};
