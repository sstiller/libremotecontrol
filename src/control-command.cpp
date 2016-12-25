/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * control-command.cpp
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

// local includes
#include "control-command.h"
#include "set-linux-servo-pwm-command.h"


ControlCommand::ControlCommand(FunctionCode code)
: functionCode(code)
{
}

// static
ControlCommand ControlCommand::deserialize(const std::vector<char>& data)
{
  if(data.size() < sizeof(FunctionCode))
  {
    return(ControlCommand(FunctionCode::Undefined));
  }
  
  FunctionCode fc = static_cast<FunctionCode>((data.at(0) << 8) | (data.at(1)));
  try{
    switch(fc)
    {
      case FunctionCode::SetLinuxServoPwm:
      {
        return(SetLinuxServoPwmCommand(data, sizeof(FunctionCode)));
        break;
      }
/*      case FunctionCode::SetLinuxGpioOutput:
      {
        break;
      }
      case FunctionCode::UpdateLinuxGpioInput:
      {
        break;
      }*/
      default:
        return(ControlCommand(FunctionCode::Undefined));
    } //switch

  }catch(std::exception& exc)
  {
    //TODO print error
    return(ControlCommand(FunctionCode::Undefined));
  }
}   
     
ControlCommand::FunctionCode ControlCommand::getFunctionCode() const
{
  return(functionCode);
}

