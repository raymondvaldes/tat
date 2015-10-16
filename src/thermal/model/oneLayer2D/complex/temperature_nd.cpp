//
//  temperature.cpp
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/temperature_nd.h"
#include "math/transform/inverseHankel.h"
#include "thermal/model/oneLayer2D/complex/h.h"
#include "thermal/model/oneLayer2D/complex/h_surface.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex {

using math::transform::inverseHankel_complex;
using math::transform::iHankelSettings;

auto temperature_nd
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r,
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  assert( z >= 0 );
  assert( r >= 0 );
  assert( b > 0 );
  assert( l > 0 );
  
  auto h_sys =
  std::function< units::quantity< units::si::dimensionless, std::complex<double> >
  ( units::quantity< units::si::dimensionless, double > const,
    units::quantity< units::si::dimensionless, double > const)>();

  auto const at_surface = z == 0 ;
  auto const in_layer = z > 0 ;
  
  if( at_surface )
  {
    h_sys = [ b, l, z ]( auto const nu_ , auto const /*z_*/ ) noexcept {
        return h_surface( nu_, l, b );
    };
  }
  else if( in_layer )
  {
    h_sys = [ b, l, z ]( auto const nu_ , auto const z_ ) noexcept {
      return h( nu_, z_, l, b );
    };
  }
  else
  {
    throw 1;
  }
  
  
  auto settings = iHankelSettings();
  settings.nu_end = 100;

  auto const T = inverseHankel_complex( h_sys , z, r, settings ) ;
  
  assert( isfinite( T.value().real() ) );
  assert( isfinite( T.value().imag() ) );
  
  return T;

}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
