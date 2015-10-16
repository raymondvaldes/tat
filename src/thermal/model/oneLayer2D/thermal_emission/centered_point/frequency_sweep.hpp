//
//  frequency_sweep.hpp
//  tat
//
//  Created by Raymond Valdes on 9/8/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef frequency_sweep_cpp_090815_centered_point
#define frequency_sweep_cpp_090815_centered_point

#include <vector>

#include "units.h"
#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace centered_point{

auto
frequency_sweep
(
  units::quantity< units::si::dimensionless > const b ,
  units::quantity< units::si::temperature > const deltaT ,
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> std::vector< math::complex::properties< units::si::temperature > > ;

} // namespace centered_point
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* frequency_sweep_cpp */
