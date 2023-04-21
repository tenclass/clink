#include "socket.h"
#include "logger.h"

Socket::Socket(){
}

Socket::Socket(uuid_t uuid){
  uuid_copy(uuid_, uuid);
}

Socket::~Socket() {
}