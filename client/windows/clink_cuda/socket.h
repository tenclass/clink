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
