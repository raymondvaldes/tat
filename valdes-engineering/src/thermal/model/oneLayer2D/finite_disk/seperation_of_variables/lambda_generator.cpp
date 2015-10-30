//
//  lambda_generator.cpp
//  tat
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "lambda_generator.hpp"
#include "math/special_functions/bessel_j/J0.h"
#include "math/special_functions/bessel_j/J1.h"
#include "math/bisection.hpp"
#include <cmath>
#include "thermal/model/oneLayer2D/finite_disk/dimensionless/thermal_penetration.h"
using namespace units;

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace seperation_of_variables{

//private

auto
Lambda_generator::objective_function( Lambda const lambda )
const noexcept -> double
{
  using math::special_functions::bessel::J1;
  using math::special_functions::bessel::J0;
  
  auto const bi2 = biot_radial;
  
  auto const x = lambda * s;


  auto const zero = -bi2 * s * J0( x ) + x * J1( x );
  
  return zero;
}

auto Lambda_generator::search_bounds()
const noexcept-> Search_bound
{
  assert( objective_function( 0 ) != 0 );
  auto const delta = M_PI_4;
  
  auto const initial_lower_bound = double(0);
  auto lower_bound = initial_lower_bound;
  auto upper_bound = lower_bound + delta;
  
  if( !empty() ) {
    lower_bound = lambdas.back().value() + delta ;
    upper_bound = lower_bound +  delta  ;
  }

  auto f_x_lower = objective_function( lower_bound );
  auto f_x_upper = objective_function( upper_bound );
  
  auto no_zero = ( f_x_lower * f_x_upper ) > 0;
  
  while ( no_zero ) {
    upper_bound += delta  ;
    
    f_x_lower = objective_function( lower_bound );
    f_x_upper = objective_function( upper_bound );
    no_zero = ( f_x_lower * f_x_upper ) > 0;
  } ;
  
  assert( f_x_lower * f_x_upper <= 0 );

  assert( lower_bound >= 0 );
  assert( upper_bound > 0 );
  assert( lower_bound < upper_bound );

  return Search_bound( lower_bound, upper_bound );
}

auto Lambda_generator::push_back_lambda()
const noexcept -> void
{
  auto const f_x = [&]( double const value ) noexcept {
    auto lambda = Lambda( value );
    return objective_function( lambda );
  };


  //solve f(x) = 0 in the interval
  auto const bounds = search_bounds();
  
  auto const f_x_lower = f_x( bounds.lower );
  auto const f_x_upper = f_x( bounds.upper) ;
  
  auto const tol = 1e-12;
  auto const solver = math::solve( f_x , bounds.lower, bounds.upper,  f_x_lower, f_x_upper , tol);
  assert( solver.pass );
  
  auto const x = solver.returnSoln();
  assert( x >= 0 ) ;

  auto const lambda = Lambda( x );
  auto const cmplx_lambda = complex_lambda( lambda, l );


  lambdas.push_back( lambda );
  complex_lambdas.push_back( cmplx_lambda );
  
  assert( lambdas.size() == complex_lambdas.size() );
}

auto Lambda_generator::size()
const noexcept -> size_t
{
  auto const size = lambdas.size();
  auto const size_c = complex_lambdas.size();
  assert( size == size_c ) ;
  return size;
}

auto Lambda_generator::empty()
const noexcept -> bool
{
  auto const is_empty = lambdas.empty();
  auto const is_c_empty = complex_lambdas.empty();
  assert( is_empty == is_c_empty );
  
  return is_empty;
}

Lambda_generator::Lambda_generator
(
  disk::dimensionless::Radius_s const s,
  disk::Biot const biot_radial,
  dimensionless::Thermal_penetration const l
): s(s), biot_radial( biot_radial ), l(l)
{
  assert( s > 0 );
  assert( biot_radial > 0);
  assert( l > 0 );
  
  //setup first 10 lambdas!
  generate_lambdas_upto( 5 );
}

auto
Lambda_generator::generate_lambdas_upto( size_t nth )
const noexcept -> void
{
  assert( isfinite( nth ) );
  assert( nth >= 0 );

  while( nth >= size() ) {
      push_back_lambda();
  }
  
  assert(  nth < size() );
}



auto
Lambda_generator::real_lambda_at
(
  size_t const nth
)
const -> Lambda
{
  assert( isfinite( nth ) );

  generate_lambdas_upto( nth );
  
  auto const lambda = lambdas.at( nth );
  
  return lambda;
}

auto
Lambda_generator::complex_lambda_at
(
  size_t const nth
) const noexcept -> Complex_lambda
{
  assert( isfinite( nth ) );

  generate_lambdas_upto( nth );
  
  auto const lambda_complex = complex_lambdas.at( nth );
  return lambda_complex;
}

auto Lambda_generator::check_s_infinite_assumption() const -> bool
{
  

  return false;
}

  
  

} // seperation_of_variables
} // finite_disk
} // oneLayer2d
} // model
} // thermal
