//
//  signal.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__signal__
#define __tat__signal__


#include <iostream>

#include "units/si/si.h"

namespace thermal {

namespace emission {
  
  
template< typename signalType >
class Signal{

private:
  units::quantity< units::si::wavelength>  electromagneticWavelength;
  units::quantity< signalType>  intensity;

public:
  explicit Signal( units::quantity< units::si::wavelength> const & wavelength_in,
                   units::quantity< signalType> const & intensity_in )
                   noexcept
  : electromagneticWavelength( wavelength_in ), intensity( intensity_in ) {};

  auto getElectromagneticWavelength() const noexcept
  -> units::quantity< units::si::wavelength>
  {
    return electromagneticWavelength ;
  }

  auto getIntensity() const noexcept
  -> units::quantity< signalType>
  {
    return intensity ;
  }
  
  auto if_wavelength( units::quantity< units::si::wavelength > const & lambda  )
  const noexcept-> bool
  {
    auto const value = 1e-14;
    auto const tol = units::quantity< units::si::wavelength>::from_value( value ) ;
      
    return ( units::abs( electromagneticWavelength - lambda ) < tol ) ;
  }
};


template<typename signalType>
std::ostream& operator<<(std::ostream& out, const Signal<signalType>& mySignal)
{
    out << mySignal.getElectromagneticWavelength() <<  "\t"
        << mySignal.getIntensity() ;
    return out;
}

template<typename signalType>
bool operator< ( Signal<signalType> const & first, Signal<signalType> const & second)
{
    return ( first.getElectromagneticWavelength() < second.getElectromagneticWavelength() );
}

template<typename signalType>
bool operator> ( Signal<signalType> const & first, Signal<signalType> const & second)
{
    return ( first.getElectromagneticWavelength() > second.getElectromagneticWavelength() );
}

template<typename signalType>
bool operator<= ( Signal<signalType> const & first, Signal<signalType> const & second)
{
    return ( first.getElectromagneticWavelength() <= second.getElectromagneticWavelength() );
}

template<typename signalType>
bool operator>= ( Signal<signalType> const & first, Signal<signalType> const & second)
{
    return ( first.getElectromagneticWavelength() >= second.getElectromagneticWavelength() );
}

template<typename signalType>
bool operator== ( Signal<signalType> const & first, Signal<signalType> const & second)
{
    return ( first.getElectromagneticWavelength() == second.getElectromagneticWavelength() );
}

}

}

#endif /* defined(__tat__signal__) */
