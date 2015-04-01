//
//  average_surface_phases_amplitudes.h
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_average_surface_phases_amplitudes__
#define __tat_thermal_model_tbc2009_average_surface_phases_amplitudes__

#include "units.h"
#include <utility>
#include <vector>
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"

namespace thermal {
namespace model {
namespace tbc2009{

auto
average_surface_phases_amplitudes
(
  units::quantity< units::si::dimensionless > const view_radius,
  std::vector< units::quantity< units::si::frequency > > const frequencies,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_substrate 
) noexcept -> std::vector< std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> > >;

} // namespace tbc2009
} // namespace thermal
} // namespace model

#endif /* defined(__tat__average_surface_phases_amplitudes__) */
