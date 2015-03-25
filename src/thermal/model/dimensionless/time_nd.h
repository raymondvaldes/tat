//
//  time.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_dimensionless_time__
#define __tat_thermal_model_dimensionless_time__

#include "units.h"

namespace thermal {

namespace model {

namespace dimensionless {

auto time
(
  units::quantity< units::si::time > const t,
  units::quantity< units::si::time > const reference
)
noexcept -> units::quantity< units::si::dimensionless >;
  
} // namespace dimensionless
  
} // namespace model

} // namespace thermal

#endif /* defined(__tat_thermal_model_dimensionless_time__) */
