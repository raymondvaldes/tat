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
  units::quantity< units::si::length>  electromagneticWavelength;
  units::quantity< signalType>  intensity;

public:
  explicit Signal( units::quantity< units::si::length> const & wavelength_in,
                   units::quantity< signalType> const & intensity_in )
                   noexcept
  : electromagneticWavelength( wavelength_in ), intensity( intensity_in ) {};

  auto getElectromagneticWavelength() const noexcept
  -> units::quantity< units::si::length>
  {
    return electromagneticWavelength ;
  }

  auto getIntensity() const noexcept
  -> units::quantity< signalType>
  {
    return intensity ;
  }
};


template<typename signalType>
std::ostream& operator<<(std::ostream& out, const Signal<signalType>& mySignal)
{
    out  <<mySignal.getElectromagneticWavelength() <<  "\t"
        << mySignal.getIntensity() ;
    return out;
}


}

}

#endif /* defined(__tat__signal__) */
