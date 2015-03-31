//
//  phases_amplitudes.h
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_complexT_phases_amplitudes__
#define __tat_thermal_model_tbc2009_complexT_phases_amplitudes__

#include "units.h"
#include <utility>
#include <vector>
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT {

auto phases_amplitudes
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r, 
  std::vector< dimensionless::HeatingProperties > const & hp,
  dimensionless::ThermalProperties const tp
) noexcept -> std::vector< std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> > >;
  
} // complexT
} // tbc2009
} // model
} // thermal

#endif /* defined(__tat__phases_amplitudes__) */
