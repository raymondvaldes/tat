//
//  surface_temperature.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/two_layer/complex/surface_temperature.h"
#include "thermal/model/two_layer/complex/temperature.h"

using namespace units;

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

auto surface_temperature
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_1,
  units::quantity< units::si::thermal_diffusivity > const alpha_2,
  units::quantity< units::si::thermal_conductivity > const k_1,
  units::quantity< units::si::thermal_conductivity > const k_2
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >
{
  auto const x = quantity<si::length>::from_value(0);
  return temperature( x, w, L, alpha_1, alpha_2, k_1, k_2 );
}

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal
