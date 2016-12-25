/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * slave.h
 * Copyright (C) 2016 Sandro Stiller <sandro@sagichnicht.de>
 *
 * libremotectl is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libremotectl is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SLAVE_H_
#define _SLAVE_H_

// stl
#include <array>

// boost
#include <boost/asio.hpp>
#include <boost/signals2.hpp>

using namespace boost::signals2;
// local includes
#include "control-command.h"

namespace bs2 = boost::signals2;

class Slave
{
public:
   Slave(std::shared_ptr<boost::asio::io_service> ioService, unsigned short port = 2345);

   bs2::signal<void(std::shared_ptr<ControlCommand>)> NewControlCommandSignal;
   bs2::signal<void(std::string)> ProtocolErrorSignal;
private:
  // functions
  void startReceive();
  void handleReceive(const boost::system::error_code& error,
                     std::size_t transferred);

  void createControlCommand(const std::vector<char>& data);

private:
  std::shared_ptr<boost::asio::io_service> ioService;
  boost::asio::ip::udp::socket udpSocket;
  boost::asio::ip::udp::endpoint remoteEndpoint;
  std::vector<char> udpRcvData;
};

#endif // _SLAVE_H_

