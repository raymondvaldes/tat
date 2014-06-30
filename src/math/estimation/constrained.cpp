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
#include <cmath>
#include <boost/assert.hpp>

#include "math/estimation/constrained.hpp"
#include "math/utilities/equalto.h"

using std::vector;

using std::abs;
using std::exp;
using std::log;

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
  BOOST_ASSERT( x_min < x_max ) ;

  double
  x = x_max ;
  x -= x_min ;
  x /= 1 + exp(xi) ;
  x += x_min ;

  constexpr double tol = 1e-10;

  if( abs( x - x_min ) < tol ) x = x_min + tol ;
  if( abs( x - x_max ) < tol ) x = x_max - tol ;
  /// Must build in some type of tolerance to ensure that xi is never >= the
  /// constraints. This causes errors when I'm transforming back and forth.

  BOOST_ASSERT_MSG( x < x_max , "\nerror!! in x_limiter2");
  BOOST_ASSERT_MSG( x > x_min , "\nerror!! in x_limiter2");

  return x ;
}

double kx_limiter1( const double ki ) {
    //converts value to k-space
  BOOST_ASSERT(ki > 0);
  return log(ki);
}

double kx_limiter2( const double ki, const double k_min, const double k_max ) {
  BOOST_ASSERT( ki >= k_min ) ;
  BOOST_ASSERT( ki <= k_max ) ;
  
  using math::equalto;
  double ki_adjusted = ki;
  
  constexpr double tol = 1e-14;
  
  if( equalto( ki, k_min ) ) {
    ki_adjusted = k_min + tol ;
  }
  else if ( equalto( ki, k_max ) ) {
    ki_adjusted = k_max - tol ;
  }
  
  
  
  return log( ( ( k_max - k_min ) / ( ki_adjusted - k_min ) ) - 1 ) ;
}

std::vector<double> x_to_kspace_unity( const double* x, const size_t n ) {
  BOOST_ASSERT( n > 0 ) ;
  
  const size_t unity_start = 0;
  const size_t unity_end = 1;
  
  vector<double> x_output( n ) ;
  for( size_t i = 0 ; i < n ; ++i ) {
    x_output[i] = kx_limiter2( x[i], unity_start, unity_end ) ;
  }
  
  
  return x_output;
}



}}
