//
//  gamma.cpp
//  tat
//
//  Created by Raymond Valdes on 3/31/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "gamma.h"


namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

using namespace units;

auto gamma
(
  units::quantity< units::si::thermal_effusivity > const e_coat,
  units::quantity< units::si::thermal_effusivity > const e_sub
) noexcept -> units::quantity< units::si::dimensionless >
{
  return e_sub / e_coat ;
}

auto eCoat_from_gamma
(
  units::quantity< units::si::dimensionless > const gamma,
  units::quantity< units::si::thermal_effusivity > const e_sub
) noexcept -> units::quantity< units::si::thermal_effusivity >
{
  // gamma = e_sub / e_coat
  auto const e_coat = e_sub / gamma;
  return e_coat;
}

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal
