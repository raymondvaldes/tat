//
//  angular_frequency.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/two_layer/dimensionless/angular_frequency.h"
#include "thermal/model/dimensionless/angular_frequency.h"

using namespace units;

namespace thermal {
namespace model {
namespace twoLayer {
namespace dimensionless {

auto angular_frequency
(
  units::quantity< units::si::angular_frequency > const omega,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > alpha_1
)
noexcept -> units::quantity< units::si::dimensionless >
{
  auto const reference =
  quantity< si::angular_frequency >( alpha_1 * radians /  (L * L) ) ;
  auto const w_non = model::dimensionless::angular_frequency(omega, reference );
  
  return w_non;
}

} // namespace dimensionless
} // namespace twoLayer
} // namespace model
} // namespace thermal
