//
//  avg_surface_phase_amplitude.h
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_complex_avg_surface_phase_amplitude__
#define __tat_thermal_model_oneLayer2D_complex_avg_surface_phase_amplitude__

#include "units.h"

#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

auto avg_surface_phase_amplitude
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius
) noexcept -> math::complex::properties< units::si::temperature >  ;

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__avg_surface_phase_amplitude__) */
