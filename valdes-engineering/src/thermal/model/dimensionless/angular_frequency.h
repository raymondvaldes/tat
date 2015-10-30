//
//  angular_frequency.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_dimensionless_angular_frequency__
#define __tat_thermal_model_dimensionless_angular_frequency__

#include "units.h"

namespace thermal {

namespace model {

namespace dimensionless {

auto angular_frequency
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::angular_frequency > const reference
) -> units::quantity< units::si::dimensionless >;
  
} // namespace dimensionless
  
} // namespace model

} // namespace thermal

#endif /* defined(__tat_thermal_model_dimensionless_angular_frequency__) */
