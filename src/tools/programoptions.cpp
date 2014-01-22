/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
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
#include <iostream>
#include <sstream>
#include "boost/program_options.hpp"

namespace tools{

bool loadProgramOptions( int argc, char** argv, std::string& path )
{
  namespace po = boost::program_options;

  po::options_description desc("Allowed options");
  desc.add_options()
      ("help", "produce help message")
      ("config,c", po::value<std::string>(&path),"set path to config.xml")
      ("version,v", "display version information")
      ;

  po::variables_map vm;
  po::store( po::command_line_parser( argc, argv ).options( desc ).run(), vm ) ;
  po::notify( vm ) ;

  if (vm.count("help"))
  {
    std::cout << desc << "\n";
    return false;
  }

  if (vm.count("config"))
  {
    std::cout << "path configured... " << path << "\n";
    return true;
  }

  if (vm.count("version"))
  {
    std::cout << "tat (Ubuntu 0.54) 0.54\n" ;
    std::cout << "Copyright (C) 2013 Raymond Valdes\n" ;
    std::cout << "This is free software; see the source for copying " ;
    std::cout << "conditions.  There is NO\n" ;
    std::cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A" ;
    std::cout << " PARTICULAR PURPOSE.\n" ;
    return false;
  }
  return true;
}


}
