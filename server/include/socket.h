#ifndef _CLINK_SOCKET_H
#define _CLINK_SOCKET_H

#include <string>
#include <uuid/uuid.h>

#define SOCKET_BUFFER_SIZE 10 * 1024 * 1024

class Socket {
public:
  Socket();
  Socket(uuid_t uuid);
  virtual ~Socket ();

  virtual bool Accept(uint16_t port) = 0;
  virtual bool Read(void* data, size_t size) = 0;
  virtual bool Write(void* data, size_t size) = 0;

protected:
  uuid_t uuid_;
};

#endif
