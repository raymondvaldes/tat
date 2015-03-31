//
//  surface_phase_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "surface_phase_amplitude.h"
#include "thermal/model/tbc2009/complexT/phase_amplitude.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT {

using namespace units;

auto surface_phase_amplitude
(
  units::quantity< units::si::dimensionless > const r, 
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp
) noexcept -> std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> >
{
  auto const z_surface = quantity< si::dimensionless >(0);
  return phase_amplitude( z_surface , r, hp, tp );
}
  
} // complexT
} // tbc2009
} // model
} // thermal
