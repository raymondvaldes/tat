//
//  frequency_sweep.hpp
//  tat
//
//  Created by Raymond Valdes on 8/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef frequency_sweep_082515_cpp
#define frequency_sweep_082515_cpp

#include <vector>

#include "units.h"
#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace offset_detector{

auto
frequency_sweep
(
  units::quantity< units::si::dimensionless > const b1_beamRadius ,
  units::quantity< units::si::temperature > const deltaT ,
  units::quantity< units::si::dimensionless > const b2_viewRadius ,
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha,
  units::quantity< units::si::dimensionless > const detector_offset
)
noexcept -> std::vector< math::complex::properties< units::si::temperature > > ;

} // namespace offset_point
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
#endif /* frequency_sweep_cpp */
