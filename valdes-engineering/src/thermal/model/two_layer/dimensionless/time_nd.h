//
//  time_nd.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_twoLayer_dimensionless_time_nd__
#define __tat_thermal_model_twoLayer_dimensionless_time_nd__

#include "units.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace dimensionless {

auto time
(
  units::quantity< units::si::time > const x,
  units::quantity< units::si::thermal_diffusivity > const alpha_1,
  units::quantity< units::si::length> const L
)
noexcept -> units::quantity< units::si::dimensionless >;

} // namespace dimensionless
} // namespace twoLayer
} // namespace model
} // namespace thermal

#endif /* defined(__tat_thermal_model_twoLayer_dimensionless_time_nd__) */
