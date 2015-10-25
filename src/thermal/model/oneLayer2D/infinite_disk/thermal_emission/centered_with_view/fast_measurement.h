//
//  fast_measurement.h
//  tat
//
//  Created by Raymond Valdes on 5/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__fast_measurement_97643_
#define __tat__fast_measurement_97643_

#include <complex>

#include "units.h"
#include "math/transform/inverseHankel.h"
#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace centered_with_view{

auto fast_measurement
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::dimensionless > const r_e ,
  math::transform::iHankelSettings const & settings =
  math::transform::iHankelSettings{ /* default! */}
)
noexcept -> math::complex::properties< units::si::temperature >;
}
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__fast_measurement__) */
