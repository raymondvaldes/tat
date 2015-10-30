//
//  transient_analysis.h
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__transient_analysis_13452346562346_
#define __tat__transient_analysis_13452346562346_

#include <vector>
#include <utility>

#include "math/functions/cosine.h"
#include "thermal/equipment/detector/Measurements.h"
#include "thermal/pyrometry/twoColor/periodic/results.h"
#include "units.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

auto transient_analysis
(
  thermal::equipment::detector::Measurements const & measurements_1,
  thermal::equipment::detector::Measurements const & measurements_2,
  units::quantity< units::si::dimensionless > const gCoeff,
  units::quantity< units::si::frequency > const laser_frequency,
  units::quantity< units::si::plane_angle > const laser_phase
)
noexcept -> transient_analysis_results;

} // namespace periodic
} // namespace twoColor
} // namespace napyrometryme
} // namespace thermal

#endif /* defined(__tat__transient_analysis__) */
