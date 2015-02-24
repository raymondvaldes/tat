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
  emission::Signal< signalType > const & first,
  emission::Signal< signalType > const & second,
  units::quantity< units::absolute< units::si::temperature > > const & Temp_Abs )
  noexcept
  -> units::quantity< units::si::dimensionless >
{
  using units::si::constants::C2_wien;
  using units::quantity;
  using units::si::temperature;
  using std::exp;
  using std::log;
  
  auto const Temp = quantity< temperature >::from_value( Temp_Abs.value() ) ;
  auto const SR = signalRatio( first, second ) ;
  auto const lambda_one = first.getElectromagneticWavelength();
  auto const lambda_two = second.getElectromagneticWavelength();
  
 // std::cout << SR <<"\t" << C2_wien <<"\t"<< lambda_one << "\t" << lambda_two << "\t" << Temp << "\n";
  
  auto
  gCoeff  =  ( C2_wien / lambda_one - C2_wien / lambda_two ) / Temp ;

  gCoeff += 5 * log( lambda_one / lambda_two ) ;
  gCoeff = exp( gCoeff ) ;
  gCoeff /= SR ;
  
  return gCoeff;
};

} // namespace twoColor

} // namespace pyrometry

} // namespace thermal

#endif /* defined(__tat__calibrationCoefficient__) */
