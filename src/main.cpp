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
//Standard Template Libraries
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
//#define NDEBUG

//Internal dependencies
#include "tools/tools.hpp"
#include "investigations/sensitivityvaldes2013.hpp"

int main( int argc, char *argv[ ] )
{
  std::cout << "Welcome back, Raymond!\n\n" ;
  stopwatch globalStopWatch ;

  std::string path;
  if( tools::programoptions::loadOptions( argc, argv, path ) )
  {
    const filesystem::directory dir1( path + "/" + "APS-77um" ) ;
    investigations::sensitivityvaldes2013::run( dir1 ) ;

    const filesystem::directory dir2( path + "/" + "APS-300um" ) ;
    investigations::sensitivityvaldes2013::run( dir2 ) ;
  }

  std::cout << "\nStopwatch: " << std::setprecision(3)
            <<  globalStopWatch.returnTime() << " sec.\n\n";

  return 0;
}
