//
//  ThermalProperties.cpp
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "ThermalProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless {

ThermalProperties::ThermalProperties
(
  units::quantity< units::si::dimensionless > const gamma_,
  units::quantity< units::si::dimensionless > const a_sub_,
  units::quantity< units::si::dimensionless > const c_coat_
) noexcept
: gamma( gamma_ ), a_sub( a_sub_ ), c_coat( c_coat_ )
{};

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal
