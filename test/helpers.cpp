// helpers.cpp
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
#include "helpers.h"

void printHex(const std::vector<char>& data)
{
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
}


