/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <iostream>
#include <sstream>
#include <boost/program_options.hpp>
#include <boost/version.hpp>
#include <boost/predef.h>
#include <gsl/gsl_version.h>
#include "tools/programoptions/programoptions.hpp"

namespace tools{

namespace programoptions{
 
void MainArguments::loadOptions( void ) const noexcept
{
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

bool MainArguments::help( void ) const noexcept
{
  return false;
}

bool MainArguments::version(void) const noexcept
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

bool MainArguments::build(void) const noexcept
{
  using std::cout;

  cout << "Built with\n";
  cout << "----------" << "\n\n" ;
  
  cout << "Boost:\n"
            << BOOST_VERSION / 100000     << "."  // major version
            << BOOST_VERSION / 100 % 1000 << "."  // minior version
            << BOOST_VERSION % 100                // patch level
            << "\n\n";
  
  cout << "Gnu Scientific Library: \n"
            << GSL_MAJOR_VERSION  << "."          // minior version
            << GSL_MINOR_VERSION                  // patch level
            << "\n\n";

  cout << "Compiler info: \n"
      << __VERSION__ << "\n";
  
  return false;
}

bool MainArguments::run_analysis( void ) const noexcept {
  return run;
}

std::string MainArguments::run_directory( void ) const noexcept {
  return path;
}

std::string MainArguments::run_samples( void ) const noexcept {
  return sampleName;
}

std::string MainArguments::run_investigationName( void ) const noexcept {
  return investigationName;
}
  


MainArguments::MainArguments( const int argc_in, const char **argv_in ) noexcept
  : argc( argc_in ), argv( argv_in )
{
  loadOptions();
}





}}
