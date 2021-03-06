//
//  deltaT.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/infinite_disk/dimensional/deltaT.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace dimensional{

using namespace units;

auto deltaT
(
  units::quantity< units::si::power > const I,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_conductivity> const k
) noexcept -> units::quantity< units::si::temperature >
{
  assert( I > 0 * watts );
  assert( L > 0 * meter );
  assert( k > 0 * watts/ ( meter * kelvin ) );
  
  auto const dT = I / ( L * k ) ;
  
  assert( isfinite( dT ) );
  return dT;
}

} // namespace dimensional
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
