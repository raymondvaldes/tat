//
//  average_surface_phase_amplitude.h
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_tbc2009_offset_Detector_average_surface_phase_amplitude__
#define __tat_tbc2009_offset_Detector_average_surface_phase_amplitude__

#include "units.h"
#include <utility>
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT {
namespace offset_detector {

auto average_surface_phase_amplitude
(
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::dimensionless > const offset,
  units::quantity< units::si::dimensionless > const view_radius
) noexcept -> std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> >;
  
} // namespace offset_detector
} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined() */
