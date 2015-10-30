//
//  thermal_penetration.cpp
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/thermal_penetration.h"
#include "thermal/define/lthermal.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace dimensionless{


auto thermal_penetration
(
  units::quantity< units::si::frequency > const f,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity> const alpha
) noexcept -> units::quantity< units::si::dimensionless >
{
  auto const l = thermal::define::thermal_penetration( alpha, f, L) ;
  return l;
}

} // namespace dimensionless
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
