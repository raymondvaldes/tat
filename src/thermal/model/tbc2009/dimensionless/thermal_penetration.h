//
//  thermal_penetration.h
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_dimensionless_thermal_penetration__
#define __tat_thermal_model_tbc2009_dimensionless_thermal_penetration__

#include "units.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

auto thermal_penetration
(
  units::quantity< units::si::frequency > const f,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity> const alpha
) noexcept -> units::quantity< units::si::dimensionless >;

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined() */
