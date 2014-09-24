/*----------------------------------------------------------------------------*\
  ========                  |
     ||     T Thermal       | TAT: Thermal Analysis Toolbox
     ||     A Analysis      |
     ||     T Toolbox       | Copyright (C) 2013 Raymond Valdes
     ||                     |
--------------------------------------------------------------------------------
License                                                                         
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or 
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your 
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
    Public License for more details.

    You should have received a copy of the GNU General Public License along with 
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/
#include <iostream>

#include "tools/programoptions/programoptions.hpp"
#include "tools/timing.h"
#include "investigations/execute.h"

using std::string;
using std::cout;
using tools::programoptions::MainArguments;

auto executeAnalysis( const MainArguments& runArgs ) -> string
{
  auto globalStopWatch = tools::stopwatch{} ;
  
  investigations::execute(
    runArgs.run_directory(),
    runArgs.run_samples(),
    runArgs.run_investigationName()
    ) ;
  
  return globalStopWatch.readoutLoud();
}

int main( const int argc, const char *argv[ ] ) {
  const auto runArgs = MainArguments{ argc, argv };
  const auto runAnalysis = runArgs.run_analysis();
  
  if( runAnalysis ) {
    const auto exeTimer = executeAnalysis( runArgs ) ;
    cout << exeTimer << "\n" ;
  }
  
  return 0 ;
}