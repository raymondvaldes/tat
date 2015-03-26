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
  units::quantity< units::si::frequency > const f,
  slab::Slab const & first_layer,
  slab::Slab const & second_layer
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >
{
  auto const x = quantity<si::length>::from_value(0);
  auto const surface_temp = temperature( x, f, first_layer, second_layer );
  return surface_temp;
}

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal
