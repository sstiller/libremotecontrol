/* -*- Mode: C++;" indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * master.h
 * Copyright (C) 2016 Sandro Stiller <sandro.stiller@gmx.de>
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

#ifndef _MASTER_H_
#define _MASTER_H_

// stl
#include <memory>

// boost
#include <boost/asio.hpp>

// local includes
#include "control-command.h"


class Master
{
public:
  Master(std::shared_ptr<boost::asio::io_service> ioService, const std::string& ipAddress, unsigned short port = 2345);

  void sendCommand(const ControlCommand& command);
   
private:
  std::shared_ptr<boost::asio::io_service> ioService;
  boost::asio::ip::udp::socket udpSocket;
  boost::asio::ip::udp::endpoint receiverEndpoint;
     
  std::vector<char> udpSendData;
   
};

#endif // _MASTER_H_

