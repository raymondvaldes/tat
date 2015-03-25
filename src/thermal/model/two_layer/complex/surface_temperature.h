//
//  surface_temperature.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_twoLayer_complex_surface_temperature__
#define __tat_thermal_model_twoLayer_complex_surface_temperature__

#include "units.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

auto surface_temperature
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_1,
  units::quantity< units::si::thermal_diffusivity > const alpha_2,
  units::quantity< units::si::thermal_conductivity > const k_1,
  units::quantity< units::si::thermal_conductivity > const k_2
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >;

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal

#endif /* defined(__tat_thermal_model_twoLayer_complex_surface_temperature__) */
