//
//  point_measurement.cpp
//  tat
//
//  Created by Raymond Valdes on 6/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/point_measurement.h"
#include "thermal/model/oneLayer2D/infinite_disk/complex/surface_phase_amplitude.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {

auto point_measurement
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_offset
)
noexcept -> math::complex::properties< units::si::temperature >
{
  auto const dT = deltaT;
  auto const r_d = view_offset;
  auto const T = oneLayer2D::complex::surface_phase_amplitude( r_d, b, l, dT);

  return T;
}

} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
