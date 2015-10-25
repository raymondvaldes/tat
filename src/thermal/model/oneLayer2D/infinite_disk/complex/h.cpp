//
//  h.cpp
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include "thermal/model/oneLayer2D/infinite_disk/complex/h.h"
#include "thermal/model/oneLayer2D/infinite_disk/complex/kappa.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using namespace units;
///this function has issues when nu -> inf (approx 1000)
auto h
(
  units::quantity< units::si::dimensionless, double > const nu,
  units::quantity< units::si::dimensionless, double > const z,
  units::quantity< units::si::dimensionless, double > const l,
  units::quantity< units::si::dimensionless, double > const b
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  assert( nu >= 0) ;
  assert( z >= 0 ) ;
  assert( l > 0) ;
  assert( b > 0 ) ;

  auto const inv = []( auto const e ) noexcept { return quantity<si::dimensionless>(1.) / e ; } ;
  
  auto const k = kappa( nu, b, l );
  auto const two = quantity<si::dimensionless>( 2 );
  auto const four = quantity<si::dimensionless>( 4 );
  
  auto const denominator = sinh( k * inv(b) );
  
  
  auto h_eval =
  exp( -pow<2>( nu )/ four ) * cosh( k * ( inv(b) - z ) ) * csch( k * inv(b) )
  / ( two * k ) ;
  
  auto const is_overflow =
  isinf( denominator.value().real() ) || isinf( denominator.value().imag() );

  if( is_overflow ) {
    h_eval = quantity< si::dimensionless, std::complex< double > >(
      std::complex< double >( 0 , 0 ) );
    std::cout <<cosh( k * ( inv(b) - z ) ) << "\t" <<csch( k * inv(b) ) << "\n";
  }
 
  assert( isfinite( h_eval.value().real() ) ) ;
  assert( isfinite( h_eval.value().imag() ) ) ;

  return h_eval;
}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
