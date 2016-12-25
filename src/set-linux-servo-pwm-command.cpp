/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * set-linux-servo-pwm-command.cpp
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

// stl
#include <stdexcept>

// local includes
#include "set-linux-servo-pwm-command.h"


SetLinuxServoPwmCommand::SetLinuxServoPwmCommand(uint8_t pwmDevice, uint8_t pwmChannel, int8_t value)
: ControlCommand(FunctionCode::SetLinuxServoPwm),
  pwmDevice(pwmDevice),
  pwmChannel(pwmChannel),
  value(value)
{
}

SetLinuxServoPwmCommand::SetLinuxServoPwmCommand(const std::vector<char>& data, uint8_t offset)
: ControlCommand(FunctionCode::SetLinuxServoPwm)
{
  if(data.size() < (offset + dataSize()))
  {
    std::string msg("Error: Not enough data for SetLinuxServoPwmCommand: ");
    msg += std::to_string(data.size()) + " < " + std::to_string(offset + dataSize());
    throw(std::runtime_error(msg));
  }
  pwmDevice = data.at(offset++);
  pwmChannel = data.at(offset++);
  value = data.at(offset++);
  //TODO: check min/max value
  if((value < -100) || (value > 100))
  {
    throw(std::runtime_error("Error: servo value invalid (-100...+100)!"));
  }
}

std::vector<char> SetLinuxServoPwmCommand::serialize() const
{
  std::vector<char> retVector = ControlCommand::serialize();
  retVector.push_back(pwmDevice);
  retVector.push_back(pwmChannel);
  retVector.push_back(value);
  return(retVector);
}

unsigned int SetLinuxServoPwmCommand::dataSize()
{
  return(sizeof(pwmDevice) + sizeof(pwmChannel) + sizeof(value));
}

