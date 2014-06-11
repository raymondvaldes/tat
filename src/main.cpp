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
#include <cstdio>
//#define BOOST_DISABLE_ASSERTS
#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_SYSTEM_NO_DEPRECATED
#include "tools/tools.hpp"
#include "investigations/sensitivityvaldes2013.hpp"
#include "investigations/num_method2014.h"

int main( const int argc, char *argv[ ] )
{
  using std::string;
  using std::vector;
  using std::cout;
  
  using tools::programoptions::loadOptions;
  std::pair< bool, string > run_analysis = loadOptions( argc, argv ) ;
  
  if( run_analysis.first )
  {
    cout << "Welcome back, Raymond!\n\n" ;
    stopwatch globalStopWatch ;

    using boost::filesystem::path;
    vector< path > folders_of_samples = filesystem::ls( run_analysis.second );
    for( const path& folder : folders_of_samples )
    {
      const filesystem::directory dir( folder.string() ) ;
      investigations::sensitivityvaldes2013::run( dir ) ;
      //investigations::num_method::run( dir ) ;
    }

    cout << globalStopWatch.readoutLoud() << "\n";
  }

  return 0;
}