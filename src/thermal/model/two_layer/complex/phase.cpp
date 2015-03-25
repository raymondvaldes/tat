//
//  phase.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>

#include "thermal/model/two_layer/complex/phase.h"
#include "thermal/model/two_layer/complex/temperature.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

using namespace units;

auto phase
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::frequency > const f,
  slab::Slab const & first_layer,
  slab::Slab const & second_layer
)
noexcept -> units::quantity< units::si::plane_angle >
{
  auto const temp = complex::temperature( x, f, first_layer, second_layer );
  auto const phase = -arg( temp ) - M_PI_2 * radians ;

  return phase;
}

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal
