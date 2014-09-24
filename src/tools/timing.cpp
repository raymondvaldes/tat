/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
-------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "tools/timing.h"

namespace tools{

stopwatch::stopwatch(void)
{
    start();
}

auto stopwatch::checktime(void) -> std::chrono::high_resolution_clock::time_point
{
    return std::chrono::high_resolution_clock::now();
}

auto stopwatch::start(void) -> void
{
    startTime = checktime();
}

auto stopwatch::stop(void) -> void
{
    stopTime = checktime();
    clockSpan = std::chrono::duration_cast
            <std::chrono::duration<double>>(stopTime- startTime);
}

auto stopwatch::returnTime(void) -> double
{
    stop();
    return clockSpan.count();
}

auto stopwatch::readoutLoud( void ) -> std::string
{
  std::ostringstream output;
  output << "Stopwatch: " << std::setprecision(3)
         <<  returnTime() << " sec.\n";
  return output.str();
}

}


