//
//  thermal_penetration.h
//  tat
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef thermal_penetration_h_101815
#define thermal_penetration_h_101815

#include "units.h"
#include "thermal/model/oneLayer2D/finite_disk/disk/thermal_diffusivity.h"
#include "thermal/model/oneLayer2D/finite_disk/laser_beam/radius.h"
#include "thermal/model/oneLayer2D/finite_disk/laser_beam/modulation_frequency.h"

namespace thermal { namespace model { namespace oneLayer2D { namespace finite_disk { namespace dimensionless{

using Thermal_penetration = units::quantity< units::si::dimensionless >;

auto
thermal_penetration(
  disk::Thermal_diffusivity const alpha,
  laser_beam::Modulation_frequency const frequency,
  laser_beam::Radius const R_heat
) noexcept -> Thermal_penetration;
  
} } } } } // namespace



#endif /* thermal_penetration_h */
