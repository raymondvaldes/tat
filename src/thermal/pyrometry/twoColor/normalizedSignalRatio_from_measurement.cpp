//
//  normalizedSignalRatio_from_measurement.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "assert/assertExtensions.h"

#include "thermal/pyrometry/twoColor/normalizedSignalRatio_from_measurement.h"

#include "thermal/pyrometry/twoColor/normalizedSignalRatio.h"
#include "thermal/pyrometry/twoColor/calibratedSignalRatio.h"
#include "thermal/pyrometry/twoColor/signalRatio.h"

using thermal::pyrometer::twoColor::signalRatio;
using thermal::pyrometer::twoColor::calibratedSignalRatio;
using thermal::pyrometer::twoColor::normalizedSignalRatio;

namespace thermal {

namespace pyrometry {

namespace twoColor {

auto normalizedSignalRatio_from_measurement(
  units::quantity<units::si::wavelength> const first_w,
  units::quantity<units::si::electric_potential> const first_signal,
  units::quantity<units::si::wavelength> const second_w,
  units::quantity<units::si::electric_potential> const  second_signal,
  units::quantity< units::si::dimensionless > const gCoeff )
  noexcept -> units::quantity< units::si::one_over_temperature >
{
  assert_gt_zero(first_w);
  assert_gt_zero(second_w);
  assert_lt(first_w, second_w);
  
  assert_gt_zero(first_signal);
  assert_gt_zero(second_signal);
  assert_gt_zero(gCoeff);

  auto const SR = signalRatio(  first_signal , second_signal ) ;
  
  auto const gSR = calibratedSignalRatio( SR, gCoeff ) ;
  
  auto const normalizedSR = normalizedSignalRatio( gSR, first_w, second_w );
  
  return normalizedSR ;
}
  
} // namespace twoColor
  
} // namespace pyrometry
  
} // namespace thermal
