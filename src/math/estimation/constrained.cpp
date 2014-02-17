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

#include "math/estimation/constrained.hpp"
#include <cmath>
#include <iostream>

namespace math{
namespace estimation{

double x_limiter1( const double xi )
{
    return exp(xi) ;
}

double x_limiter2( const double xi, const double x_min, const double x_max )
{
  // converts value from k-space to x_space. In k-space the parameter is free
  // to be any value.  In x-space the parameter is constrained between x_min
  // and x_max.

  double
  x = x_max ;
  x -= x_min ;
  x /= 1 + exp(xi) ;
  x += x_min ;

  if( x > x_max || x < x_min )
  {
    std::cerr << "\nerror!! in x_limiter2" << x << "\t" << x_min ;
    std::cerr << "\t" << x_max << "\n" ;
  }

  return x ;
}

double kx_limiter1( const double ki )
{
    //converts value to k-space
//    assert(ki > 0);
    return log(ki);
}

double kx_limiter2( const double ki, const double k_min, const double k_max )
{
//    assert(ki > k_min  && ki < k_max);
    return log( ( (k_max - k_min) / (ki - k_min) ) - 1.);
}

}}
