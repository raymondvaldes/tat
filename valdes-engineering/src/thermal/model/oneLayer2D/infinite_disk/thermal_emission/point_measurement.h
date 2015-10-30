//
//  point_measurement.h
//  tat
//
//  Created by Raymond Valdes on 6/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__point_measurement_235246_
#define __tat__point_measurement_235246_

#include "units.h"
#include "math/complex/properties.h"
#include <complex>

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
noexcept -> math::complex::properties< units::si::temperature >;

} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__point_measurement__) */
