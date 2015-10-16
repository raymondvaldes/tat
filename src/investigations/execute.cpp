/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include <algorithm>
#include <boost/filesystem.hpp>

#include "investigations/execute.h"
#include "investigations/num_method2014.h"
#include "investigations/sensitivityvaldes2013.hpp"
#include "investigations/taylor_uncertainty.h"
#include "investigations/twoColorPyrometery.h"
#include "investigations/bulkDiffusivityMeasurements2015/run.hpp"

#include "algorithm/algorithm.h"
#include "tools/interface/filesystem.hpp"

using algorithm::for_each;

namespace investigations {

void execute
(
  const std::string& mydirectory,
  const std::string& sampleName,
  const std::string& investigationName
) noexcept
{
  using filesystem::directory;
  auto const run_investigation = [ & ] ( const directory& active ) -> void
  {
    if( investigationName == "PIE_Analsis") {
      sensitivityvaldes2013::run( active ) ;
    }
    else if( investigationName == "1d_Numerical") {
      num_method::run( active ) ;
    }
    else if( investigationName == "taylor_uncertainty") {
      taylor_uncertainty::run( active ) ;
    }
    else if( investigationName == "twoColorPyrometery" ) {
      twoColorPyrometery::run( active ) ;
    }
    else if( investigationName == "bulkDiffusivityMeasurements2015" ){
      bulkDiffusivityMeasurements2015::run( active ) ;
    }
    
    else {
      using std::cout;
      cout << "No investigation selected.\n" ;
    }
  };
  
  auto const directory_of_samples = directory{ mydirectory } ;
  
  auto const directory_is_sample =
  directory_of_samples.working_directory_starts_with( sampleName ) ;
  
  if( directory_is_sample )
  {
    run_investigation( directory_of_samples ) ;
  }
  else
  {
    auto const paths = directory_of_samples.ls() ;
    
    for_each( paths , [&]( auto const & path )
    {
      if( path.working_directory_starts_with( sampleName ) ) {
        run_investigation( path ) ;
      }
    });
  }
  
}}
