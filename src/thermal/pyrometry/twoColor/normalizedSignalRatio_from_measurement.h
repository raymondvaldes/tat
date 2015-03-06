//
//  normalizedSignalRatio_from_measurement.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__normalizedSignalRatio_from_measurement__
#define __tat__normalizedSignalRatio_from_measurement__

#include "units.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {

auto normalizedSignalRatio_from_measurement(
  units::quantity<units::si::wavelength> const & first_w,
  units::quantity<units::si::electric_potential> const & first_signal,
  units::quantity<units::si::wavelength> const & second_w,
  units::quantity<units::si::electric_potential> const &  second_signal,
  units::quantity< units::si::dimensionless > const & gCoeff )
  noexcept -> units::quantity< units::si::one_over_temperature >;
  
} // namespace twoColor
  
} // namespace pyrometry
  
} // namespace thermal

#endif /* defined(__tat__normalizedSignalRatio_from_measurement__) */
