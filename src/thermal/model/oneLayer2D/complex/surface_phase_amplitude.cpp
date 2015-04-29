//
//  surface_phase_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/surface_phase_amplitude.h"
#include "thermal/model/oneLayer2D/complex/phase_amplitude.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using namespace units;

auto surface_phase_amplitude
(
  units::quantity< units::si::dimensionless > const r,
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT
) noexcept -> math::complex::properties< units::si::temperature >
{
  assert( r >= 0 );
  assert( b > 0 );
  assert( l > 0 );
  assert( deltaT > 0 * kelvin );

  auto const z_surface = quantity< si::dimensionless >( 0 )  ;

  return phase_amplitude( z_surface, r, b, l, deltaT );
}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
