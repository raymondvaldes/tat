//
//  temperatureMeasurement.cpp
//  tat
//
//  Created by Raymond Valdes on 1/22/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include "thermal/pyrometry/twoColor/temperatureSteady.h"
#include "thermal/pyrometry/twoColor/calibratedSignalRatio.h"
#include "units/si/constants/thermal.h"

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto temperatureSteady(
  const units::quantity< units::si::dimensionless > calibrationCoefficient,
  const units::quantity< units::si::dimensionless > signalRatio,
  std::pair<
    units::quantity< units::si::length > ,
    units::quantity< units::si::length> > const & wavelength )
  noexcept -> units::quantity< units::si::temperature>
{
  assert( wavelength.first.value() > 0 ) ;
  assert( wavelength.second.value() > 0 ) ;
  assert( wavelength.first < wavelength.second ) ;
  assert( calibrationCoefficient.value()> 0 ) ;

  using thermal::pyrometer::twoColor::calibratedSignalRatio;
  using units::si::constants::C2_wien;
  using std::log;
  
  auto const SR = signalRatio ;
  auto const G = calibrationCoefficient;
  auto const gSR = calibratedSignalRatio( SR, G );
  
  auto
  temp = C2_wien / wavelength.first - C2_wien / wavelength.second ;
  temp /= log( gSR ) - 5 * log( wavelength.first / wavelength.second );

  return temp;
}


} // namespace twoColor

} // namespace pyrometer

} // namespace thermal
