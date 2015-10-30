//
//  surface_phases_amplitudes.h
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_complex_surface_phases_amplitudes__
#define __tat_thermal_model_oneLayer2D_complex_surface_phases_amplitudes__

#include "units.h"
#include <complex>
#include <vector>
#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

auto surface_phases_amplitudes
(
  units::quantity< units::si::dimensionless > const r,
  units::quantity< units::si::dimensionless > const b,
  std::vector< units::quantity< units::si::dimensionless > > const ls,
  units::quantity< units::si::temperature > const deltaT
) noexcept -> std::vector< math::complex::properties< units::si::temperature >>;

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__surface_phases_amplitudes__) */
