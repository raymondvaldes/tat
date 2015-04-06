//
//  average_surface_phases.h
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_offsetDetector_average_surface_phases__
#define __tat_thermal_model_tbc2009_offsetDetector_average_surface_phases__

#include "units.h"
#include <utility>
#include <vector>
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace offset_detector {

auto
average_surface_phases
(
  std::vector< units::quantity< units::si::frequency > > const frequencies,
  dimensionless::HeatingProperties const & hp,
  dimensionless::ThermalProperties const & tp,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_substrate,
  units::quantity< units::si::dimensionless > const offset,
  units::quantity< units::si::dimensionless > const view_radius
) noexcept -> std::vector< units::quantity< units::si::plane_angle >  >;


} // namespace offset_detector
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined(__tat__average_surface_phases__) */
