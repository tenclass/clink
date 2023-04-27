/* 
 * Clink
 * Copyright (C) 2023 cair <rui.cai@tenclass.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
