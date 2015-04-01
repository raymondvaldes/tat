//
//  gamma.h
//  tat
//
//  Created by Raymond Valdes on 3/31/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_model_tbc2009_dimensionless_gamma__
#define __tat_model_tbc2009_dimensionless_gamma__

#include "units.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

auto gamma
(
  units::quantity< units::si::thermal_effusivity > const e_coat,
  units::quantity< units::si::thermal_effusivity > const e_sub
) noexcept -> units::quantity< units::si::dimensionless >;

auto eCoat_from_gamma
(
  units::quantity< units::si::dimensionless > const gamma,
  units::quantity< units::si::thermal_effusivity > const e_sub
) noexcept -> units::quantity< units::si::thermal_effusivity >;



} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined() */
