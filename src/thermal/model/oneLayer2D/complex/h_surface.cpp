//
//  h_surface.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/h_surface.h"
#include "thermal/model/oneLayer2D/complex/kappa.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using namespace units;

auto h_surface
(
  units::quantity< units::si::dimensionless, double > const nu,
  units::quantity< units::si::dimensionless, double > const l,
  units::quantity< units::si::dimensionless, double > const b
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  assert( nu >= 0) ;
  assert( l > 0) ;
  assert( b > 0 ) ;

  auto const inv = []( auto const e ) noexcept { return quantity<si::dimensionless>(1.) / e ; } ;
//  auto const coth = []( auto const e ) noexcept { return cosh(e)/sinh(e); } ;

  auto const k = kappa( nu, b, l );
  auto const two = quantity<si::dimensionless>( 2 );
  auto const four = quantity<si::dimensionless>( 4 );
  
  auto const e = k * inv(b);
  auto const c1 = cosh(e) ;
  auto const c2 = sinh(e) ;
  auto const a1 = coth( k * inv(b) );
  auto const a2 = ( two * k );
  auto const a3 = exp( -pow<2>( nu )/ four );
  
  auto const h_eval = exp( -pow<2>( nu )/ four ) * coth( k * inv(b) )
  / ( two * k ) ;
 
  assert( isfinite( h_eval.value().real() ) ) ;
  assert( isfinite( h_eval.value().imag() ) ) ;

  return h_eval;
}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
