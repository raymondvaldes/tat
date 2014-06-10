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
//#define BOOST_DISABLE_ASSERTS
#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_SYSTEM_NO_DEPRECATED

//Internal dependencies
#include "tools/tools.hpp"
#include "investigations/sensitivityvaldes2013.hpp"
#include "investigations/num_method2014.h"
#include "math/utility.hpp"

int main( int argc, char *argv[ ] )
{
  using std::string;
  using std::vector;
  using std::cout;
  
  
  string myDirectory;
  using tools::programoptions::loadOptions;
  const bool run_analysis = loadOptions( argc, argv, myDirectory ) ;
  if( run_analysis )
  {
    cout << "Welcome back, Raymond!\n\n" ;
    stopwatch globalStopWatch ;

    using boost::filesystem::path;
    vector< path > samples = filesystem::ls( myDirectory );
    for( const path& testSpeciman : samples )
    {
      const string specimanPath = testSpeciman.string() ;
      const filesystem::directory dir( specimanPath ) ;
      investigations::sensitivityvaldes2013::run( dir ) ;
      //investigations::num_method::run( dir ) ;
    }

    cout << globalStopWatch.readoutLoud() << "\n";
  }

  return 0;
}
