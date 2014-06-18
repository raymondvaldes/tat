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
#include "tools/interface/filesystem.hpp"

namespace investigations {

void execute( const std::string& mydirectory ) {

  using std::vector;
  using std::string;
  using filesystem::directory;
  const directory directory_of_samples( mydirectory ) ;
  
  const string sampleName = "APS" ;
  
  const auto investigations = []( const directory& active ) {
    sensitivityvaldes2013::run( active ) ;
  };
  
  const bool
  runCurrentDirectory =
  directory_of_samples.working_directory_starts_with( sampleName ) ;
  
  std::cout << runCurrentDirectory << "\n";
  
  if( runCurrentDirectory ) {
    investigations( directory_of_samples ) ;
  }
  else {
    const vector< directory > paths = directory_of_samples.ls() ;
    for( const directory& active : paths ) {
      if( active.working_directory_starts_with( sampleName ) ) {
        investigations( active ) ;
      }
    }
  }
  

}}