//
//  fitted_measurements.h
//  tat
//
//  Created by Raymond Valdes on 3/22/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__fitted_measurements__
#define __tat__fitted_measurements__

#include "thermal/equipment/detector/measurements.h"
#include "math/curveFit/cosine.h"
#include "units.h"

namespace thermal {
  
namespace equipment {

namespace detector {

auto fitted_measurements
(
  Measurements const & m,
  units::quantity< units::si::frequency > const f
)
noexcept -> math::functions::Cosine< units::si::electric_potential >;

auto fitted_measurements
(
  Measurements const & m,
  units::quantity< units::si::angular_frequency > const omega
)
noexcept -> math::functions::Cosine< units::si::electric_potential >;

} // namespace detector
  
} // namespace equipment
  
} // namespace thermal

#endif /* defined(__tat__fitted_measurements__) */
