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
#include "tools/programoptions/programoptions.hpp"

namespace tools{

namespace programoptions{



void MainArguments::loadOptions( void ) const
{
  //function modifie 'path' and 'run'

  using std::make_pair;
  
  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
      ( "help", "produce help message")
      ("run,r",
         po::value<std::string>(&path),
        "set path to settings folder")
      ("version,v", "display version information")
      ("build,b","build libraries")
      ("sample,s",
         po::value<std::string>(&sampleName),
         "folder with sample files starts with this [string]")
      ("investigation,i",
         po::value<std::string>(&investigationName),
         "name of investigation to be executed [string]")
         ;
  po::variables_map vm ;

  try
  {
    po::store( po::command_line_parser( argc,argv ).options(desc).run(), vm ) ;
  }
  catch ( std::exception const&  ex )
  {
    std::cout << "See help below...\n" ;
    version() ;
    run = help( /*desc*/ ) ;
  }

  po::notify( vm ) ;

  if( vm.count( "help" ) )
    { run = help( /*desc*/ ) ; }

  if( vm.count( "run" ) )
    { run = true ; }

  if( vm.count( "version" ) )
    { run = version() ; }

  if( vm.count( "build" ) )
    { run = build() ; }
  
  if( vm.count( "sample" ) ) {}
  if( vm.count( "investigation" ) ) {}
}

bool MainArguments::help( void ) const
{
  return false;
}

bool MainArguments::version(void) const
{
  std::cout << "\nT A T : " ;
  std::cout << "Thermal Analysis Toolbox\n";
  std::cout << "Copyright (C) 2013 Raymond Valdes\n\n" ;
  std::cout << "This is free software; see the source for copying " ;
  std::cout << "conditions.  There is NO\n" ;
  std::cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A" ;
  std::cout << " PARTICULAR PURPOSE.\n\n" ;

  std::cout << "Writted by : \nRaymondValdes\n\n";
  std::cout << "Contributors:\n";
  std::cout << "Ted Bennett\n";
  std::cout << "Michael Simeone\n\n";
  return false;
}

bool MainArguments::build(void) const
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

bool MainArguments::run_analysis( void ) const {
  return run;
}

std::string MainArguments::run_directory( void ) const {
  return path;
}

std::string MainArguments::run_samples( void ) const {
  return sampleName;
}

std::string MainArguments::run_investigationName( void ) const {
  return investigationName;
}
  


MainArguments::MainArguments( const int argc_in, const char **argv_in )
  : argc( argc_in ), argv( argv_in )
{
  loadOptions();
}





}}