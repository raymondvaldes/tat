//
//  HeatingProperties.cpp
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "HeatingProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless {

HeatingProperties::HeatingProperties
(
  units::quantity< units::si::dimensionless > const Lambda_,
  units::quantity< units::si::dimensionless > const R0_,
  units::quantity< units::si::dimensionless > const R1_,
  units::quantity< units::si::dimensionless > const b_
) noexcept
:
//l( l_ ),
 Lambda( Lambda_ ), R0( R0_ ), R1( R1_ ), b( b_ )
{};

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal
