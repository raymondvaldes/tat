//
//  detector_emission.h
//  tat
//
//  Created by Raymond Valdes on 5/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_123423_detector_emission__
#define __tat_123423_detector_emission__

#include "units.h"
#include "math/complex/properties.h"
#include <complex>

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

auto detector_emission
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  units::quantity< units::si::temperature> const T_steady_state,
  units::quantity< units::si::wavelength> const detector_wavelength
) noexcept -> std::complex< double >;


} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__detector_emission__) */
