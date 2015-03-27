//
//  J2.cpp
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "J2.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{
namespace radiosity{

auto J2
(
  units::quantity< units::si::dimensionless > const R0,
  units::quantity< units::si::dimensionless > const R1,
  units::quantity< units::si::dimensionless > const Lambda
) noexcept -> units::quantity< units::si::dimensionless >
{
  using namespace units;
  
  auto const
  J = ( 1 - R1 ) * exp( - Lambda )
      / ( 1 - R0 * R1 * exp( -2 * Lambda ) );

  return J;
}

} // namespace radiosity
} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal
