//
//  predictedTemperature.h
//  tat
//
//  Created by Raymond Valdes on 10/2/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_predictedTemperature_h
#define tat_predictedTemperature_h

#include "units.h"

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto temperatureSteady(
  const units::quantity< units::si::dimensionless > calibrationCoefficient,
  const units::quantity< units::si::dimensionless > signalRatio,
  const units::quantity< units::si::length > wavelength_one,
  const units::quantity< units::si::length > wavelength_two
  ) noexcept
  -> units::quantity< units::si::temperature>;
  
} // namespace twoColor

} // namespace pyrometer

} // namespace thermal

#endif
