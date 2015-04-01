/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <cmath>
#include <boost/assert.hpp>
#include <algorithm>

#include "math/estimation/constrained.hpp"
#include "math/utilities/equalto.h"

using std::vector;

using std::abs;
using std::exp;
using std::log;

namespace math{
namespace estimation{

double x_limiter1( const double xi ) noexcept
{
  auto const output = double(exp( xi ));
  assert( output > 0 );
  return output ;
}

double x_limiter2( const double xi, const double x_min, const double x_max ) noexcept
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

double kx_limiter1( const double ki ) noexcept {
    //converts value to k-space
  BOOST_ASSERT(ki > 0);
  return log(ki);
}

double kx_limiter2( const double ki, const double k_min, const double k_max ) noexcept {
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

vector<double> x_to_kspace_unity( const double* x, const size_t n ) noexcept {
  BOOST_ASSERT( n > 0 ) ;
  
  typedef const size_t unity;
  unity start = 0 ;
  unity finish = 1 ;
  
  vector<double> x_output( n, 0 ) ;
  
  for( size_t i = 0 ; i < n ; ++i ) {
    x_output[i] = kx_limiter2( x[i], start, finish ) ;
  }
  return x_output;
}

vector<double> kspace_to_x_unity( const double* x, const size_t n ) noexcept {
  BOOST_ASSERT( n > 0 ) ;
  
  typedef const size_t unity;
  unity start = 0 ;
  unity end = 1 ;
  
  vector<double> x_output( n ) ;
  for( size_t i = 0 ; i < n ; ++i ) {
    x_output[i] = x_limiter2( x[i], start, end ) ;
  }
  
  return x_output;
}



}}
