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
#include "Header.h"
#include "boost/program_options.hpp"

int main( int argc, char *argv[ ] )
{
  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help", "produce help message")
      ("compression", po::value<int>(), "set compression level") ;

  po::variables_map vm;
  po::store( po::command_line_parser( argc, argv ).options( desc ).run(), vm );
  po::notify(vm);

  if (vm.count("help"))
  {
    std::cout << desc << "\n";
    return 1;
  }

  if (vm.count("compression"))
  {
    std::cout << "Compression level was set to "
         << vm["compression"].as<int>() << ".\n";
  }
  else
  {
    std::cout << "Compression level was not set.\n";
  }


  std::cout << "Welcome back, Raymond!\n\n";
  class stopwatch globalStopWatch;

  /// Retrieve working directory
  const std::string path("/home/raymond/code/tat/bin");
  const class filesystem::directory dir(path);

  /// Run investigations
  investigations::sensitivityvaldes2013::run( dir );

//  //Prepare figures and data for paper Sensitivity
////    SensitivityValdes2013::CC_APS2(poptea);
////    SensitivityValdes2013::figureSensitivityIntro(poptea);

  /// Test investigation
//  investigations::manyfit::run( dir );

  globalStopWatch.displayTime();
  return 0;
}
