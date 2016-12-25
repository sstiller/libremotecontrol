/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * control-command.h
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

#ifndef _CONTROL_COMMAND_H_
#define _CONTROL_COMMAND_H_

// C
#include <cstdint>

// stl
#include <vector>
#include <memory>


class ControlCommand
{
  // types:
public:
  enum class FunctionCode: uint16_t
  {
    Undefined = 0,
    SetLinuxServoPwm,
    SetLinuxGpioOutput,
    UpdateLinuxGpioInput,
    NumControlCommands
  };

  // functions, Xtors
protected:
  ControlCommand() = delete;
  ControlCommand(FunctionCode code);

public:
  /** Parses received UDP data.
    * @returns undefined ControlCommand on parsing error
    */
  static std::shared_ptr<ControlCommand> deserialize(const std::vector<char>& data);

  /** Serializes the data of the command object.
    * children reimplement this function, but call this one first
    */
  virtual std::vector<char> serialize() const;
   
  FunctionCode getFunctionCode() const;


  // variables
private:
  const FunctionCode functionCode;
  
};

#endif // _CONTROL_COMMAND_H_

