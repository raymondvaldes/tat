//
//  signal.cpp
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "thermal/emission/signal.h"


namespace thermal {
namespace emission {


//Constructor
Signal::Signal( const units::quantity< units::si::length> wavelength_in,
                const units::quantity< units::si::electric_potential> intensity_in )
: wavelength( wavelength_in ), intensity( intensity_in ) {}

units::quantity< units::si::length> Signal::getWavelength() const {
 return wavelength ;
}

units::quantity< units::si::electric_potential> Signal::getIntensity() const {
  return intensity ;
}
  
}}