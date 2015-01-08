/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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

#include <boost/filesystem.hpp>
#include "investigations/execute.h"
#include "investigations/num_method2014.h"
#include "investigations/sensitivityvaldes2013.hpp"
#include "investigations/taylor_uncertainty.h"
#include "investigations/twoColorPyrometery.h"

#include "tools/interface/filesystem.hpp"

namespace investigations {

void execute( const std::string& mydirectory, const std::string& sampleName,
              const std::string& investigationName ) noexcept {

  using filesystem::directory;
  const auto investigations = [ & ] ( const directory& active ) -> void
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
    else {
      using std::cout;
      cout << "No investigation selected.\n" ;
    }
  };
  
  
  const auto directory_of_samples = directory{ mydirectory } ;
  
  const auto runCurrentDirectory =
  directory_of_samples.working_directory_starts_with( sampleName ) ;
  
  if( runCurrentDirectory ) {
    investigations( directory_of_samples ) ;
  }
  else {
    const auto paths = directory_of_samples.ls() ;
    for( const directory& active : paths ) {
      if( active.working_directory_starts_with( sampleName ) ) {
        investigations( active ) ;
      }
    }
  }
  
}}
