//
//  thermal_penetration.cpp
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal_penetration.h"
#include "thermal/define/lthermal.h"
namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

using namespace units;

auto thermal_penetration
(
  units::quantity< units::si::frequency > const f,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity> const alpha
) noexcept -> units::quantity< units::si::dimensionless >
{
  auto const l =  thermal::define::thermal_penetration( alpha, f, L) ;
  return l;
}

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal
