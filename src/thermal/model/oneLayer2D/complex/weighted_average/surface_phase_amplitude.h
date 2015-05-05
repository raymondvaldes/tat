//
//  surface_phase_amplitude.h
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__surface_phase_amplitude__
#define __tat__surface_phase_amplitude__

#include "units.h"

#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{
namespace weighted_average{

auto surface_phase_amplitude
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  units::quantity< units::si::temperature> const T_steady_state,
  units::quantity< units::si::wavelength> const detector_wavelength
) noexcept -> math::complex::properties< units::si::temperature >  ;

} // namespace weighted_average
} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__surface_phase_amplitude__) */
