//
//  spectrum.h
//  tat
//
//  Created by Raymond Valdes_New on 2/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_spectrum_h
#define tat_spectrum_h

#include <algorithm>
#include <vector>
#include "units.h"
#include "thermal/emission/signal.h"

namespace thermal {

namespace emission {

template< typename SignalType >
class Spectrum{
  using SignalList = std::vector< Signal< SignalType > >;

  const units::quantity< units::absolute <units::si::temperature > > sourceTemperature;
  
public:
  SignalList signals;

  
public:
  explicit Spectrum(
    SignalList const & inputSignals,
    units::quantity< units::absolute <units::si::temperature > > const & sourceTemperatureIn )
  noexcept : sourceTemperature( sourceTemperatureIn ), signals(inputSignals)
  {} ;
  
  explicit Spectrum(
    SignalList const & inputSignals,
    units::quantity< units::absolute<units::celsius::temperature> > const & sourceTemperatureIn
  ) noexcept:
  Spectrum( inputSignals,
  units::absolute_conv_C_to_K_type::convert( sourceTemperatureIn ))
  {}


  auto source_Temperature(void)
  noexcept -> units::quantity< units::si::temperature >
  {
    return sourceTemperature;
  }
};



  
} // namespace emission
  
} // namespace thermal

#endif
