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

  units::quantity< units::absolute <units::si::temperature > > sourceTemperature;
  
public:
  SignalList signals;

  explicit Spectrum(
    SignalList const & inputSignals,
    units::quantity< units::absolute<units::celsius::temperature> > const & sourceTemperatureIn
  ) noexcept:
  Spectrum( inputSignals,
  units::absolute_conv_C_to_K_type::convert( sourceTemperatureIn ))
  {}

  explicit Spectrum(
    SignalList const & inputSignals,
    units::quantity< units::absolute <units::si::temperature > > const & sourceTemperatureIn )
  noexcept : sourceTemperature( sourceTemperatureIn ), signals( inputSignals )
  {
    using std::is_sorted;
    using std::sort;
    using std::begin;
    using std::end;
    
    auto const fail = !is_sorted( begin( signals ), end( signals ) ) ;
    
    if( fail ) {
      sort( begin( signals ) , end( signals ) );
    }

  } ;
  

  auto source_Temperature(void)
  noexcept -> units::quantity< units::si::temperature >
  {
    return sourceTemperature;
  }
  
  auto min( void ) const noexcept -> Signal< SignalType >
  {
    return signals.front();
  }
  
  auto max( void ) const noexcept -> Signal< SignalType >
  {
    return signals.back();
  }
  
  auto if_available( units::quantity< units::si::wavelength > input )
  const noexcept
  -> bool
  {
    using std::any_of;
    using std::begin;
    using std::end;
    using units::abs;
    
    auto const pass = any_of( begin(signals), end(signals),
    [&input]( auto const &val )
    {
      auto const value = 1e-14;
      auto const tol = units::quantity< units::si::wavelength>::from_value( value ) ;
      
      return ( abs( val.getElectromagneticWavelength() - input ) < tol ) ;
    } );
    
    return pass;
  }
  
    //iterators
    typedef typename std::vector< Signal< SignalType > >::iterator iterator;
  
    typedef typename std::vector< Signal< SignalType > >::const_iterator const_iterator;


    iterator begin() { return signals.begin(); }

    const_iterator begin() const { return signals.begin(); }

    iterator end() { return signals.end(); }

    const_iterator end() const { return signals.end(); }
  
};

  
} // namespace emission
  
} // namespace thermal

#endif
