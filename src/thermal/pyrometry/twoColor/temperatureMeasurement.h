//
//  predictedTemperature.h
//  tat
//
//  Created by Raymond Valdes on 10/2/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_predictedTemperature_h
#define tat_predictedTemperature_h

#include "thermal/emission/signal.h"
#include "units/si/si.h"
#include "units/si/constants/thermal.h"

namespace thermal{
namespace pyrometer{
namespace twoColor{

inline auto temperatureSteady(   const units::quantity< units::si::dimensionless > calibrationCoefficient,
                          const units::quantity< units::si::dimensionless > signalRatio,
                          const units::quantity< units::si::length > wavelength_one,
                          const units::quantity< units::si::length > wavelength_two
                          ) noexcept -> units::quantity< units::si::temperature>
{
  using units::si::constants::C2_wien;
  using std::log;
  
  const auto SR = signalRatio ;
  const auto G = calibrationCoefficient;
  
  auto
  temp = C2_wien / wavelength_one - C2_wien / wavelength_two ;
  temp /= log( G * SR ) - 5 * log( wavelength_one / wavelength_two );

  return temp;
}

}}}
#endif
