//
//  temperature.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/temperature_nd.h"
#include "thermal/model/oneLayer2D/complex/temperature.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using namespace units;

auto temperature
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r,
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::heat_flux > const I,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_conductivity > const k
) noexcept -> units::quantity< units::si::temperature, std::complex<double> >
{
  assert( z >= 0 ) ;
  assert( r >= 0 ) ;
  assert( b > 0 ) ;
  assert( l > 0 ) ;
  
  auto const theta = temperature_nd( z, r, b, l ) ;

  auto const T =  ( I * L / k) * theta;
  
  assert( isnormal( T.value().real() )  );
  assert( isnormal( T.value().imag() )  );

  return T;
}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
