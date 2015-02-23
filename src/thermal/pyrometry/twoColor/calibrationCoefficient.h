//
//  calibrationCoefficient.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__calibrationCoefficient__
#define __tat__calibrationCoefficient__

#include "assert/assertExtensions.h"

#include "units.h"
#include "units/si/si.h"
#include "units/si/constants/thermal.h"
#include "thermal/emission/signal.h"
#include "thermal/emission/signalRatio.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {

template< class signalType >
auto calibrationCoefficient(
  const emission::Signal< signalType > first,
  const emission::Signal< signalType > second,
  const units::quantity< units::absolute< units::si::temperature > > Temp_Abs ) noexcept
  -> units::quantity< units::si::dimensionless >
{
  using units::si::constants::C2_wien;
  using std::exp;
  using std::log;
  
  auto const Temp =
    units::quantity< units::si::temperature >::from_value( Temp_Abs.value() ) ;
  
  auto const SR = signalRatio( second, first ) ;
  auto const lambda_one = first.getElectromagneticWavelength();
  auto const lambda_two = second.getElectromagneticWavelength();
  
  
  auto
  gCoeff  =  ( C2_wien / lambda_one - C2_wien / lambda_two ) / Temp ;

  gCoeff += 5 * log( lambda_two / lambda_one ) ;
  gCoeff = exp( gCoeff ) ;
  gCoeff /= SR ;
  
  return gCoeff;
};

} // namespace twoColor

} // namespace pyrometry

} // namespace thermal

#endif /* defined(__tat__calibrationCoefficient__) */
