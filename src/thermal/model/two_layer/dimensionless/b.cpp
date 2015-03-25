//
//  b.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/two_layer/dimensionless/b.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace dimensionless {

auto b
(
  units::quantity< units::si::thermal_conductivity > const k_1,
  units::quantity< units::si::thermal_conductivity > const k_2
)
noexcept -> units::quantity< units::si::dimensionless >
{
  return k_2 / k_1 ;
}

} // namespace dimensionless
} // namespace twoLayer
} // namespace model
} // namespace thermal
