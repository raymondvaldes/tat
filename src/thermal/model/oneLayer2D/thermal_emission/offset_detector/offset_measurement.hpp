//
//  offset_measurement.hpp
//  tat
//
//  Created by Raymond Valdes on 8/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef offset_measurement_cpp
#define offset_measurement_cpp

#include "units.h"
#include "math/complex/properties.h"
#include "math/transform/inverseHankel.h"
#include <complex>

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace offset_detector{

auto offset_measurement
(
  units::quantity< units::si::dimensionless > const b1_beamRadius,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::dimensionless > const b2_viewRadius ,
  units::quantity< units::si::dimensionless > const b3_view_offset,
  units::quantity< units::si::temperature > deltaT, 
  math::transform::iHankelSettings const & settings =
  math::transform::iHankelSettings{ /* default! */}
)
noexcept -> math::complex::properties< units::si::temperature >;

} // namespace offset_detector
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* offset_measurement_cpp */
