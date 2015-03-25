//
//  time_nd.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/dimensionless/time_nd.h"
#include "thermal/model/two_layer/dimensionless/time_nd.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace dimensionless {

auto time
(
  units::quantity< units::si::time > const t,
  units::quantity< units::si::thermal_diffusivity > const alpha_1,
  units::quantity< units::si::length> const L
)
noexcept -> units::quantity< units::si::dimensionless >
{
  auto const reference = L * L / alpha_1;
  return model::dimensionless::time( t, reference ) ;
}

} // namespace dimensionless
} // namespace twoLayer
} // namespace model
} // namespace thermal
