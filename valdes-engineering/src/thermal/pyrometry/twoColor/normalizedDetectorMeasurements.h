//
//  normalizedDetectorMeasurements.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__normalizedDetectorMeasurements__
#define __tat__normalizedDetectorMeasurements__

#include <vector>
#include <utility>

#include "thermal/equipment/detector/measurements.h"
#include "units.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {

auto normalizedDetectorMeasurements(
  thermal::equipment::detector::Measurements const & first,
  thermal::equipment::detector::Measurements const & second,
  units::quantity< units::si::dimensionless > const & gCoeff )
noexcept  ->
std::pair<
  std::vector< units::quantity< units::si::time > > ,
  std::vector< units::quantity< units::si::one_over_temperature > > >;
  
} // namespace twoColor
  
} // namespace pyrometry
  
} // namespace thermal

#endif /* defined(__tat__normalizedDetectorMeasurements__) */
