//
//  phase_amplitude.h
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_complex_phase_amplitude__
#define __tat_thermal_model_oneLayer2D_complex_phase_amplitude__

#include "units.h"
#include <complex>

#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

auto phase_amplitude
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r, 
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT
) noexcept -> math::complex::properties< units::si::temperature > ;

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__phase_amplitude__) */
