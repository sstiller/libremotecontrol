/* -*- Mode: C++;" indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * set-linux-servo-pwm-command.h
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

#ifndef _SET_LINUX_SERVO_PWM_COMMAND_H_
#define _SET_LINUX_SERVO_PWM_COMMAND_H_

// local includes
#include "control-command.h"


class SetLinuxServoPwmCommand: public ControlCommand 
{
public:
  SetLinuxServoPwmCommand(uint8_t pwmDevice, uint8_t pwmChannel, int8_t value);
  SetLinuxServoPwmCommand(const std::vector<char>& data, uint8_t offset);

  uint8_t getDevice() const { return(pwmDevice);};
  uint8_t getChannel() const { return(pwmChannel);};
  int8_t getValue() const { return(value);};
   
  virtual std::vector<char> serialize() const override;
  static unsigned int dataSize();
protected:

private:
 uint8_t pwmDevice;
 uint8_t pwmChannel;
 int8_t value;
};

#endif // _SET_LINUX_SERVO_PWM_COMMAND_H_

