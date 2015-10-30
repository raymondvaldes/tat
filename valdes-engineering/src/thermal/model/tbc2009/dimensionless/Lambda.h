//
//  Lambda.h
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_dimensionless_Lambda__
#define __tat_thermal_model_tbc2009_dimensionless_Lambda__

#include "units.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

auto Lambda
(
  units::quantity< units::si::length > const opticalPenetration,
  units::quantity< units::si::length > const L_coating_thickness
) noexcept -> units::quantity< units::si::dimensionless >;

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined(__tat__Lambda__) */
