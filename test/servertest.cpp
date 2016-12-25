// servertest.cpp
//
// Copyright (C) 2016 - Sandro Stiller
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

// stl
#include <iostream>
#include <iomanip>

// lib includes
#include "../src/remotectl.h"

// local includes
#include "helpers.h"

// prototypes
void commandReceived(std::shared_ptr<ControlCommand> cmd);
void protocolError(const std::string& msg);


int main(int, char** argv)
{
  std::cout << argv[0] << " started." << std::endl;
  auto ioService = std::make_shared<boost::asio::io_service>();
  Slave slave(ioService, 2345);
  
  slave.NewControlCommandSignal.connect(commandReceived);
  slave.ProtocolErrorSignal.connect(protocolError);
  
  ioService->run();

  return(0);
}

void commandReceived(std::shared_ptr<ControlCommand> cmd)
{
  switch(cmd->getFunctionCode())
  {
    case ControlCommand::FunctionCode::SetLinuxServoPwm:
    {
      auto cmd1 = std::dynamic_pointer_cast<SetLinuxServoPwmCommand>(cmd);
      if(cmd1)
      {
        std::cout << "Device  = " << (int) cmd1->getDevice()
                  << "\nChannel = " << (int) cmd1->getChannel()
                  << "\nValue   = " << (int) cmd1->getValue()
                  << std::endl;
      }else{
        std::cout << "Cast failed!" << std::endl;
      }
      break;
    }
    default:
      std::cout << "Error: unsupported function: " << (int) cmd->getFunctionCode() << std::endl;
  }
}

void protocolError(const std::string& msg)
{
  std::cout << "Protocol error, message: " << msg << std::endl; 
}

