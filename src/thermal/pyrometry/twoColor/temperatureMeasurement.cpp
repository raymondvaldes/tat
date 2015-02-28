//
//  temperatureMeasurement.cpp
//  tat
//
//  Created by Raymond Valdes on 1/22/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>

#include "thermal/pyrometry/twoColor/temperatureMeasurement.h"
#include "units/si/constants/thermal.h"

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto temperatureSteady(
  const units::quantity< units::si::dimensionless > calibrationCoefficient,
  const units::quantity< units::si::dimensionless > signalRatio,
  const units::quantity< units::si::length > wavelength_one,
  const units::quantity< units::si::length > wavelength_two
  ) noexcept
  -> units::quantity< units::si::temperature>
{
  {
    using units::quantity;
    using units::si::length;
    using units::si::dimensionless;
    
    assert( wavelength_one > quantity<length>::from_value(0) ) ;
    assert( wavelength_two > quantity<length>::from_value(0) ) ;
    assert( calibrationCoefficient > quantity<dimensionless>(0) ) ;
  }

  using units::si::constants::C2_wien;
  using std::log;
  
  auto const SR = signalRatio ;
  auto const G = calibrationCoefficient;
  
  auto
  temp = C2_wien / wavelength_one - C2_wien / wavelength_two ;
  temp /= log( G * SR ) - 5 * log( wavelength_one / wavelength_two );

  return temp;
}


} // namespace twoColor

} // namespace pyrometer

} // namespace thermal
