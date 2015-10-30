//
//  temperature.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "temperature.h"

namespace thermal {

namespace model {

namespace dimensionless {

auto temperature
(
  units::quantity< units::si::temperature > const T,
  units::quantity< units::si::temperature > const offset,
  units::quantity< units::si::temperature > const reference
)
noexcept -> units::quantity< units::si::dimensionless >
{
  using namespace units;

  auto const T_abs = absolute< quantity< si::temperature > >( T );
  auto const T_abs_offset = absolute< quantity< si::temperature > >( offset );

  auto const T_delta = quantity< si::temperature >( T_abs - T_abs_offset );
  auto const T_dimensionless = T_delta / reference;

  return T_dimensionless;
}

  
} // namespace dimensionless
  
} // namespace model

} // namespace thermal
