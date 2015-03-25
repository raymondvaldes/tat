//
//  b.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_twoLayer_dimensionless_b__
#define __tat_thermal_model_twoLayer_dimensionless_b__

#include "units.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace dimensionless {

auto b
(
  units::quantity< units::si::thermal_conductivity > const k_1,
  units::quantity< units::si::thermal_conductivity > const k_2
)
noexcept -> units::quantity< units::si::dimensionless >;

} // namespace dimensionless
} // namespace twoLayer
} // namespace model
} // namespace thermal

#endif /* defined(__tat_thermal_model_twoLayer_dimensionless_b__) */
