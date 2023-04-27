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
