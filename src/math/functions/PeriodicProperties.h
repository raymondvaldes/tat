//
//  PeriodicProperties.h
//  tat
//
//  Created by Raymond Valdes on 1/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_PeriodicProperties_h
#define tat_PeriodicProperties_h

#include <cmath>
#include <cassert>
#include "units/units.h"

namespace math {
  
namespace functions {
 
template< typename T >
class PeriodicProperties
{
private:
  auto checkInputArguments( void ) -> void
  {
    using units::si::radians;
    assert( phase <= M_PI * radians &&
            phase >= -M_PI* radians ) ;
    
    using units::si::radians_per_second;
    assert( omega > 0 * radians_per_second );
    
    assert( amplitude.value() > 0  ) ;
  };

public:
  units::quantity<T> offset;
  units::quantity<T> amplitude;
  units::quantity<units::si::angular_frequency> omega;
  units::quantity<units::si::plane_angle> phase;
  
  auto get_period() -> units::quantity< units::si::time >
  {
    return units::quantity<units::si::dimensionless>(1) / get_temporalFrequency();
  } ;
  
  auto get_angularFrequency() -> units::quantity< units::si::angular_frequency>
  {
    return omega;
  };

  auto get_temporalFrequency() -> units::quantity< units::si::frequency>
  {
    return omega / ( units::si::radians );
  };

  auto get_phase() ->units::quantity< units::si::plane_angle>
  {
    return phase;
  };

  auto get_offset() ->units::quantity<T>
  {
    return offset;
  };
  
  auto get_amplitude() -> units::quantity<T>
  {
    return amplitude;
  };
  
  
  
public:
  explicit PeriodicProperties(
    const units::quantity<T> offsetIn,
    const units::quantity<T> amplitudeIn,
    const units::quantity<units::si::angular_frequency> omegaIn,
    const units::quantity<units::si::plane_angle> phaseIn
    ) noexcept
    : offset( offsetIn), amplitude(amplitudeIn),
      omega( omegaIn ), phase(phaseIn)
    {
      checkInputArguments();
    };

  explicit PeriodicProperties(
    const units::quantity<T> offsetIn,
    const units::quantity<T> amplitudeIn,
    const units::quantity<units::si::frequency> frequencyIn,
    const units::quantity<units::si::plane_angle> phaseIn
    ) noexcept
    : offset( offsetIn), amplitude(amplitudeIn),
      omega( M_2_PI * frequencyIn ), phase(phaseIn)
    {
      checkInputArguments();
    };
  
};

} // namespace functions

} // namespace math

#endif
