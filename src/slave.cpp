/* -*- Mode: C++;" indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * slave.cpp
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

#include <boost/bind.hpp>

// local includes
#include "slave.h"



Slave::Slave(std::shared_ptr<boost::asio::io_service> ioService, unsigned short port)
: ioService(ioService),
  udpSocket(*ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    udpRcvData.reserve(512);
  startReceive();
}

void Slave::startReceive()
{
  // async_receive_from uses size() instead of capacity. So we resize the vector.
  udpRcvData.resize(udpRcvData.capacity());
  udpSocket.async_receive_from(boost::asio::buffer(udpRcvData),
                               remoteEndpoint,
                               boost::bind(&Slave::handleReceive,
                                           this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}

void Slave::handleReceive(const boost::system::error_code& error,
                          std::size_t transferred)
{
  if (!error || error == boost::asio::error::message_size)
  {
    // size is not set if receiving. So we set it here.
    udpRcvData.resize(transferred);
    createControlCommand(udpRcvData);
    startReceive();
  }
}

void Slave::createControlCommand(const std::vector<char>& data)
{
  try{
    auto cmd = ControlCommand::deserialize(data);
    NewControlCommandSignal(cmd);
  }catch(std::exception& exc)
  {
    ProtocolErrorSignal(exc.what());
  }
  
}


