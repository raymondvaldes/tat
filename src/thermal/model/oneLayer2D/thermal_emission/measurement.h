//
//  measurement.h
//  tat
//
//  Created by Raymond Valdes on 5/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

//#ifndef __tat_93353_measurement__
//#define __tat_93353_measurement__

#include "units.h"
#include "math/complex/properties.h"
#include <complex>

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {

auto measurement
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  units::quantity< units::si::temperature> const T_steady_state,
  units::quantity< units::si::wavelength> const detector_wavelength
)
noexcept -> math::complex::properties< units::si::temperature >;

} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

//#endif /* defined(__tat__measurement__) */
