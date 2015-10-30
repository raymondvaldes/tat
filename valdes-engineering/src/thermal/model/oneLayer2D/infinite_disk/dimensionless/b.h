//
//  b.h
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_dimensionless_b__
#define __tat_thermal_model_oneLayer2D_dimensionless_b__

#include "units.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace dimensionless{

auto b
(
  units::quantity< units::si::length > const beam_radius,
  units::quantity< units::si::length > const L
) noexcept -> units::quantity< units::si::dimensionless >;

} // namespace dimensionless
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__b__) */
