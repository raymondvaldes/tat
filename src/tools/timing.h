/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef TIMING_H
#define TIMING_H
#include <chrono>
#include <string>

namespace tools {
class stopwatch
{
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point stopTime;
    std::chrono::high_resolution_clock::time_point currentTime;
    std::chrono::high_resolution_clock::time_point tdel;

    std::chrono::duration<double> clockSpan;
    std::chrono::high_resolution_clock::time_point checktime(void) noexcept;

public:
    explicit stopwatch( void ) noexcept;
  
    auto start( void ) noexcept -> void ;
    auto stop( void ) noexcept -> void ;
    auto returnTime( void ) noexcept -> double ;
    auto readoutLoud( void ) noexcept -> std::string ;
};

}

#endif // TIMING_H
