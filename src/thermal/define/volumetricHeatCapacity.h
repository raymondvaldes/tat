//
//  volumetricHeatCapacity.h
//  tat
//
//  Created by Raymond Valdes_New on 3/10/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_thermal_model_volumetricHeatCapacity_h
#define tat_thermal_model_volumetricHeatCapacity_h

#include "units.h"

namespace thermal{

namespace define {

auto volumetricHeatCapacity
(
  units::quantity< units::si::thermal_diffusivity > const alpha,
  units::quantity< units::si::thermal_conductivity> const k
)
noexcept -> units::quantity< units::si::volumetric_heat_capacity >;

auto volumetricHeatCapacity
(
  units::quantity< units::si::thermal_effusivity > const e,
  units::quantity< units::si::thermal_conductivity> const k
)
noexcept -> units::quantity< units::si::volumetric_heat_capacity >;

} // namespace define
  
} // namespace

#endif
