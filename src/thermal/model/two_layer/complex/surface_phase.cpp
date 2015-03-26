//
//  surface_phase.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/two_layer/complex/surface_phase.h"
#include <iostream>
#include <cmath>
#include "thermal/model/two_layer/complex/surface_temperature.h"
#include "math/coordinate_system/wrap_to_negPi_posPi.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

using namespace units;
using math::coordinate_system::wrap_to_negPi_posPi;

auto surface_phase
(
  units::quantity< units::si::frequency > const f,
  slab::Slab const & first_layer,
  slab::Slab const & second_layer
)
noexcept -> units::quantity< units::si::plane_angle >
{
  auto const temp =
  complex::surface_temperature( f, first_layer, second_layer );

  using std::isfinite;
  assert( isfinite( temp.value().real() ) ) ;
  assert( isfinite( temp.value().imag() ) ) ;
  
  auto const phase = arg( temp ) - M_PI_2 * radians ;  

  auto const phase_wrapper = wrap_to_negPi_posPi( phase );
  return phase_wrapper;
}

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal
