//
//  average_surface_phase_amplitude.h
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__average_surface_phase_amplitude__
#define __tat__average_surface_phase_amplitude__

#include "units.h"
#include <utility>
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT {

auto average_surface_phase_amplitude
(
  units::quantity< units::si::dimensionless > const view_radius,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::dimensionless > const l 
) noexcept -> std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> >;
  
} // complexT
} // tbc2009
} // model
} // thermal

#endif /* defined(__tat__average_surface_phase_amplitude__) */
