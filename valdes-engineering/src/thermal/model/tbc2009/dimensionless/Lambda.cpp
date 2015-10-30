//
//  Lambda.cpp
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "Lambda.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

auto Lambda
(
  units::quantity< units::si::length > const opticalPenetration,
  units::quantity< units::si::length > const L_coating_thickness
) noexcept -> units::quantity< units::si::dimensionless >
{
  return opticalPenetration / L_coating_thickness;
}

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal
