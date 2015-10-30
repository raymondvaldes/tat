//
//  a.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/two_layer/dimensionless/a.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace dimensionless {

auto a
(
  units::quantity< units::si::thermal_diffusivity > const alpha_1,
  units::quantity< units::si::thermal_diffusivity > const alpha_2
)
noexcept -> units::quantity< units::si::dimensionless >
{
  using units::sqrt;
  return sqrt( alpha_2 / alpha_1 );
}

} // namespace dimensionless
} // namespace twoLayer
} // namespace model
} // namespace thermal
