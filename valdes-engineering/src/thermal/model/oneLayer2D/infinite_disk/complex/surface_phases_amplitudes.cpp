//
//  surface_phases_amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/infinite_disk/complex/surface_phases_amplitudes.h"
#include "thermal/model/oneLayer2D/infinite_disk/complex/phases_amplitudes.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using namespace units;

auto surface_phases_amplitudes
(
  units::quantity< units::si::dimensionless > const r,
  units::quantity< units::si::dimensionless > const b,
  std::vector< units::quantity< units::si::dimensionless > > const ls,
  units::quantity< units::si::temperature > const deltaT
) noexcept -> std::vector< math::complex::properties< units::si::temperature >>
{
  assert( r >= 0 );
  assert( b > 0 );
  assert( ls.size() > 0 );
  assert( deltaT > 0 * kelvin );

  auto const z_surface = quantity< si::dimensionless >( 0 )  ;

  return phases_amplitudes( z_surface, r, b, ls, deltaT );
}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
