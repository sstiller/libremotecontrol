// serialize-test.cpp
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

// local includes
#include "../src/set-linux-servo-pwm-command.h"

int main(int, char** argv)
{
  std::cout << argv[0] << " started." << std::endl;
  SetLinuxServoPwmCommand cmd1(1, 2, 100);
  auto data = cmd1.serialize();
  std::cout << std::hex;
  int lineCnt = 0;
  for(auto byte : data)
  {
    std::cout << " " <<  std::setfill('0') << std::setw(2) << (int)byte;
    if(! (++lineCnt % 8))
    {
      std::cout << std::endl;
    }
  }
  std::cout << std::dec << std::endl;

  std::shared_ptr<ControlCommand> cmd2 = ControlCommand::deserialize(data);
  if(cmd2->getFunctionCode() == ControlCommand::FunctionCode::SetLinuxServoPwm)
  {
    std::cout << "Jo!" << std::endl;
  }else{
    std::cout << (int)cmd2->getFunctionCode() << " != " <<  (int)ControlCommand::FunctionCode::SetLinuxServoPwm << std::endl;
  }
  
  data = cmd2->serialize();
  std::cout << std::hex;
  lineCnt = 0;
  for(auto byte : data)
  {
    std::cout << " " <<  std::setfill('0') << std::setw(2) << (int)byte;
    if(! (++lineCnt % 8))
    {
      std::cout << std::endl;
    }
  }
  std::cout << std::dec << std::endl;
  if(cmd2->getFunctionCode() == ControlCommand::FunctionCode::SetLinuxServoPwm)
  {
    auto cmd3 = std::dynamic_pointer_cast<SetLinuxServoPwmCommand>(cmd2);
    if(cmd3)
    {
      std::cout << "Device  = " << (int) cmd3->getDevice()
                << "\nChannel = " << (int) cmd3->getChannel()
                << "\nValue   = " << (int) cmd3->getValue()
                << std::endl;
    }else{
      std::cout << "Cast failed!" << std::endl;
    }
  }
  
  //SetLinuxServoPwmCommand cmd1(0, 1, 0);
  return(0);
}
