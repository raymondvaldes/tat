//
//  c.cpp
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "c.h"

#include "units.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

using namespace units;

auto c
(
  units::quantity< units::si::thermal_conductivity > const k_radial_r,
  units::quantity< units::si::thermal_conductivity > const k_axial_z
) noexcept -> units::quantity< units::si::dimensionless >
{
  return sqrt( k_radial_r / k_axial_z ) ;
}

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

