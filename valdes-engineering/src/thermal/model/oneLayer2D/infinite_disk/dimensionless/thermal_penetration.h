//
//  thermal_penetration.h
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_dimensionless_thermal_penetration__
#define __tat_thermal_model_oneLayer2D_dimensionless_thermal_penetration__

#include "units.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace dimensionless{

auto thermal_penetration
(
  units::quantity< units::si::frequency > const f,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity> const alpha
) noexcept -> units::quantity< units::si::dimensionless >;

} // namespace dimensionless
} // namespace oneLayer2D
} // namespace model
} // namespace thermal


#endif /* defined(__tat__thermal_penetration__) */
