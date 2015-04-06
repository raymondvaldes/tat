//
//  coating_diffusivity_from_a.h
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_mode_tbc2009_dimensionless_coating_diffusivity_from_a__
#define __tat_thermal_mode_tbc2009_dimensionless_coating_diffusivity_from_a__

#include "units.h"

namespace thermal{
namespace model{
namespace tbc2009{
namespace dimensionless{

using namespace units;

auto coating_diffusivity_from_a
(
  units::quantity< units::si::dimensionless> const a_sub,
  units::quantity< units::si::thermal_diffusivity > const alpha_substrate
) noexcept -> units::quantity< units::si::thermal_diffusivity>;


} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace therml

#endif /* defined(__tat__coating_diffusivity_from_a__) */
