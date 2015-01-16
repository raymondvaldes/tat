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

#include "algorithm/string/starts_with.h"
#include <boost/algorithm/string/predicate.hpp>

namespace algorithm {
namespace string {
  
bool starts_with( const std::string& check_this,
                  const std::string& begins_with ) noexcept
{
  //const bool lengthrequirement = check_this.length() >= begins_with.length() ;
 // BOOST_ASSERT( lengthrequirement ) ;
  using boost::starts_with;
  
  const bool pass = starts_with( check_this, begins_with ) ;
  return pass;
}

bool starts_with_not( const std::string& check_this,
                      const std::string& begins_with ) noexcept
{
  const auto startsWith = starts_with( check_this, begins_with ) ;
  return !startsWith ;
}


}}
