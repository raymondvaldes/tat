//
//  phase_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/phase_amplitude.h"
#include "thermal/model/oneLayer2D/complex/temperature.h"
#include "math/coordinate_system/wrap_to_negPi_posPi.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using namespace units;
using math::coordinate_system::wrap_to_negPi_posPi;
using math::complex::properties;

auto phase_amplitude
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r, 
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT
) noexcept -> math::complex::properties< units::si::temperature >
{
  assert( z >= 0 );
  assert( r >= 0 );
  assert( b > 0 );
  assert( l > 0 );
  assert( deltaT > 0 * kelvin );

  auto const T_complex = temperature( z, r, b, l, deltaT );
  
  auto const phase = -arg( T_complex ) ;
  auto const amplitude = abs( T_complex );

  return properties< si::temperature >( phase , amplitude );
}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
