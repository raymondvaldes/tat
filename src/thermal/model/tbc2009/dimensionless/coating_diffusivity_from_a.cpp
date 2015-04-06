//
//  coating_diffusivity_from_a.cpp
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "coating_diffusivity_from_a.h"
#include <cassert>

namespace thermal{
namespace model{
namespace tbc2009{
namespace dimensionless{

using namespace units;

auto coating_diffusivity_from_a
(
  units::quantity< units::si::dimensionless> const a_sub,
  units::quantity< units::si::thermal_diffusivity > const alpha_substrate
) noexcept -> units::quantity< units::si::thermal_diffusivity>
{
  assert( a_sub > 0 );
  assert( alpha_substrate > 0. * square_meter/second );

  auto const alpha_coat = pow<2>( a_sub ) * alpha_substrate;
  return alpha_coat;
}

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace therml

