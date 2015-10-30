//
//  signal.h
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_signal_h
#define tat_signal_h

#include "thermal/emission/signal.h"
#include "units/si/si.h"
#include "units/physical_dimensions.h"

namespace thermal {
namespace emission {
namespace blackBody {
  
  
template< class signalType >
class Signal: public thermal::emission::Signal
{
  private:
    const units::quantity< temperature_dimension> sourceTemperature;

  public:
    explicit Signal( const units::quantity< units::si::length> &wavelength_in,
                     const units::quantity< signalType> &intensity_in,
                     const units::quantity< temperature_dimension> &Temp_in ) noexcept
    : thermal::emission::Signal( wavelength_in, intensity_in ),
      sourceTemperature( Temp_in ) { };

    auto getTemperature( void ) noexcept {
      return sourceTemperature;
    }
}
  
}}}
#endif
