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

#ifndef __tat__equalto__
#define __tat__equalto__

#include <cmath>
#include <limits>


namespace math {
  
template< typename T1, typename T2 >
bool equalto ( const T1 a, const T2 b ) noexcept
{
  using std::abs;
  using std::numeric_limits;

  const double multi = ( a > b ? a : b ) ;
  const double multi2 = ( multi >= 1 ? multi  : 1 ) ;

  return ( abs(a - b) < ( numeric_limits<double>::epsilon()) * multi2 );
}  
  
}

#endif /* defined(__tat__equalto__) */