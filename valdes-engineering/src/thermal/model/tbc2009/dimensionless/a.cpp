//
//  a.cpp
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "a.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

using namespace units;

auto a
(
  units::quantity< units::si::thermal_diffusivity > const alpha_z,
  units::quantity< units::si::thermal_diffusivity > const alpha_z_coat
) noexcept -> units::quantity< units::si::dimensionless >
{
  return sqrt( alpha_z / alpha_z_coat );
}

auto alphaCoat_from_a
(
  units::quantity< units::si::dimensionless > const a,
  units::quantity< units::si::thermal_diffusivity > const alpha_sub
) noexcept -> units::quantity< units::si::thermal_diffusivity >
{
  return alpha_sub / pow<2>(a) ;
}

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal
