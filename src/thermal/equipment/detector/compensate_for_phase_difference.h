//
//  compensate_for_phase_difference.h
//  tat
//
//  Created by Raymond Valdes_New on 3/21/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_compensate_for_phase_difference_h
#define tat_compensate_for_phase_difference_h

#include <utility>
#include "units.h"
#include "thermal/equipment/detector/measurements.h"

namespace thermal {

namespace equipment {

namespace detector {

auto phase_difference
(
  std::pair< Measurements, Measurements > const & m,
  units::quantity< units::si::frequency > const freq
) -> units::quantity< units::si::plane_angle >;

auto compensate_for_phase_difference
(
  std::pair< Measurements, Measurements > const & m,
  units::quantity< units::si::frequency > const freq
) -> std::pair< Measurements, Measurements >;

} // namespace detector

} // namespace equipment

} // namespace thermal

#endif
