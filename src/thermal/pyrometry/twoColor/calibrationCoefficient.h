//
//  calibrationCoefficient.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__calibrationCoefficient__
#define __tat__calibrationCoefficient__
#include <utility>

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
    
  auto
  gCoeff  =  ( C2_wien / lambda_one - C2_wien / lambda_two ) / Temp ;

  gCoeff += 5 * log( lambda_one / lambda_two ) ;
  gCoeff = exp( gCoeff ) ;
  gCoeff /= SR ;
  
  return gCoeff;
};

template< class signalType >
auto calibrationCoefficient(
  std::pair<  units::quantity< signalType >,
              units::quantity< signalType > > const & signals,
  std::pair<  units::quantity< units::si::wavelength >,
              units::quantity< units::si::wavelength > > const & wavelengths,
  units::quantity< units::absolute< units::si::temperature > > const & Temp_Abs )
  noexcept
  -> units::quantity< units::si::dimensionless >
{
  using emission::Signal;
  auto const first = Signal<signalType>( wavelengths.first, signals.first  ) ;
  auto const second = Signal<signalType>( wavelengths.second, signals.second ) ;

  return calibrationCoefficient( first, second, Temp_Abs );
}





} // namespace twoColor

} // namespace pyrometry

} // namespace thermal

#endif /* defined(__tat__calibrationCoefficient__) */
