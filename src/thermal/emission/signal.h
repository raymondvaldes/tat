//
//  signal.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__signal__
#define __tat__signal__

#include "units/si/si.h"

namespace thermal {
namespace emission {
  
  
template< class signalType >
class Signal{

private:
  units::quantity< units::si::length> electromagneticWavelength;
  units::quantity< signalType> intensity;

public:
  explicit Signal( const units::quantity< units::si::length> &wavelength_in,
                   const units::quantity< signalType> &intensity_in ) noexcept
  : electromagneticWavelength( wavelength_in ), intensity( intensity_in ) {};



  auto getElectromagneticWavelength() const {
    return electromagneticWavelength ;
  }

  auto getIntensity() const {
    return intensity ;
  }



};




  
}}

#endif /* defined(__tat__signal__) */
