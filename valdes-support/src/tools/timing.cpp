/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "tools/timing.h"

namespace tools{

stopwatch::stopwatch(void) noexcept
{
    start();
}

auto stopwatch::checktime(void) noexcept -> std::chrono::high_resolution_clock::time_point
{
    return std::chrono::high_resolution_clock::now();
}

auto stopwatch::start(void) noexcept -> void
{
    startTime = checktime();
}

auto stopwatch::stop(void) noexcept -> void
{
    stopTime = checktime();
    clockSpan = std::chrono::duration_cast
            <std::chrono::duration<double>>(stopTime- startTime);
}

auto stopwatch::returnTime(void) noexcept -> double
{
    stop();
    return clockSpan.count();
}

auto stopwatch::readoutLoud( void ) noexcept -> std::string
{
  std::ostringstream output;
  output << "Stopwatch: " << std::setprecision(3)
         <<  returnTime() << " sec.\n";
  return output.str();
}

}


