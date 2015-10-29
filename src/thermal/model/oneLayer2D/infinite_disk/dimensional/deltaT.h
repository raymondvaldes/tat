//
//  deltaT.h
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_dimensional_deltaT__
#define __tat_thermal_model_oneLayer2D_dimensional_deltaT__

#include "units.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace dimensional{

auto deltaT
(
  units::quantity< units::si::power > const I,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_conductivity> const k
) noexcept -> units::quantity< units::si::temperature >;

} // namespace dimensional
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
#endif /* defined(__tat__deltaT__) */
