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
#include "units.h"

namespace math {
namespace functions {
 
template< typename T >
class PeriodicProperties
{
private:
  auto checkInputArguments( void ) -> void
  {
    using units::si::radians;
    using units::si::radians_per_second;
    
    assert( phase <= M_PI * radians &&
            phase >= -M_PI* radians ) ;
    assert( omega > 0 * radians_per_second );
    assert( amplitude.value() > 0  ) ;
  };

public:
  units::quantity< T > offset;
  units::quantity< T > amplitude;
  units::quantity< units::si::angular_frequency > omega;
  units::quantity< units::si::plane_angle > phase;
  
  auto get_period() const
  noexcept -> units::quantity< units::si::time >
  {
    return units::quantity<units::si::dimensionless>(1) / get_temporalFrequency();
  } ;
  
  auto get_angularFrequency() const
  noexcept -> units::quantity< units::si::angular_frequency>
  {
    return omega;
  };

  auto get_temporalFrequency() const
  noexcept -> units::quantity< units::si::frequency>
  {
    return omega / ( 2 * M_PI * units::si::radians );
  };

  auto get_phase() const
  noexcept -> units::quantity< units::si::plane_angle>
  {
    return phase;
  };
  
  auto shift_phase( units::quantity< units::si::plane_angle> shift)
  noexcept -> void
  {
    phase += shift;
  };

  auto get_offset() const
  noexcept -> units::quantity<T>
  {
    return offset;
  };
  
  auto get_amplitude() const
  noexcept -> units::quantity<T>
  {
    return amplitude;
  };
  
  
public:
  explicit PeriodicProperties(
    const units::quantity<T> offsetIn,
    const units::quantity<T> amplitudeIn,
    const units::quantity<units::si::angular_frequency> omegaIn,
    const units::quantity<units::si::plane_angle> phaseIn )
  noexcept
    : offset( offsetIn), amplitude(amplitudeIn),
      omega( omegaIn ), phase(phaseIn)
    {
      checkInputArguments() ;
    };

  explicit PeriodicProperties(
    const units::quantity<T> offsetIn,
    const units::quantity<T> amplitudeIn,
    const units::quantity<units::si::frequency> temperoralFrequency,
    const units::quantity<units::si::plane_angle> phaseIn )
  noexcept
    : PeriodicProperties( offsetIn, amplitudeIn,
      2. * M_PI * units::si::radians * temperoralFrequency, phaseIn)
    {};


  
};

} // namespace functions
} // namespace math

#endif
