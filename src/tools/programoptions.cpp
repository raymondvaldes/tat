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
#include <iostream>
#include <sstream>
#include <boost/program_options.hpp>
#include <boost/version.hpp>
#include <gsl/gsl_version.h>
#include "tools/programoptions.hpp"

namespace tools{

namespace programoptions{

bool loadOptions( int argc, char** argv, std::string& path )
{
  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help", "produce help message")
      ("config,c", po::value<std::string>(&path),
        "set path to config files dir")
      ("version,v", "display version information")
      ("build,b","build libraries")
      ;
  bool run = false;
  po::variables_map vm;

  try
  {
    po::store( po::command_line_parser( argc,argv ).options(desc).run(), vm ) ;
  }
  catch (std::exception const&  ex)
  {
    std::cout << "See help below...\n";
    version();
    run = help(desc);
  }

  po::notify( vm ) ;

  if (vm.count("help"))
    { run = help(desc) ; }

  if (vm.count("config"))
    { run = config(path) ; }

  if (vm.count("version"))
    { run = version() ; }

  if (vm.count("build"))
    { run = build() ; }

  return run;
}

bool help( boost::program_options::options_description desc)
{
  std::cout << desc << "\n";
  return false;
}

bool config( std::string& path)
{
//  std::cout << "path configured... " << path << "\n";
  return true;
}


bool version(void)
{
  std::cout << "TAT: " ;
  std::cout << "Thermal Analysis Toolbox\n";
  std::cout << "Copyright (C) 2013 Raymond Valdes\n\n" ;
  std::cout << "This is free software; see the source for copying " ;
  std::cout << "conditions.  There is NO\n" ;
  std::cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A" ;
  std::cout << " PARTICULAR PURPOSE.\n\n" ;
  return false;
}

bool build(void)
{
  std::cout << "Built with:\n";
  std::cout << "Boost "
            << BOOST_VERSION / 100000     << "."  // major version
            << BOOST_VERSION / 100 % 1000 << "."  // minior version
            << BOOST_VERSION % 100                // patch level
            << std::endl;
  std::cout << "Gnu Scientific Library "
            << GSL_MAJOR_VERSION  << "."          // minior version
            << GSL_MINOR_VERSION                  // patch level
            << std::endl;
  return false;
}


}}
