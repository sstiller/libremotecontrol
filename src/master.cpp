/* -*- Mode: C++;" indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * master.cpp
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

#include "master.h"

Master::Master(std::shared_ptr<boost::asio::io_service> ioService, const std::string& ipAddress, unsigned short port)
: ioService(ioService),
  udpSocket(*ioService)
{
  boost::asio::ip::udp::resolver resolver(*ioService);
  boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), ipAddress, std::to_string(port));
  receiverEndpoint = *resolver.resolve(query);  
    
  udpSocket.open(boost::asio::ip::udp::v4());

}

void Master::sendCommand(const ControlCommand& command)
{
  udpSendData = command.serialize();
  udpSocket.send_to(boost::asio::buffer(udpSendData), receiverEndpoint);
}



