//
//  Header.h
//  tat
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_Header_h
#define tat_Header_h

#include <cmath>
#include <cassert>
#include "units/units.h"

namespace math {
  
namespace functions {
 
template< typename T >
class Periodic
{
private:
  virtual auto evaluate( const units::quantity<units::si::time> time ) const
  noexcept  -> units::quantity<T> = 0;

protected:

  const units::quantity<T> offset;
  
  const units::quantity<T> amplitude;
  
  const units::quantity<units::si::angular_frequency> omega;

  const units::quantity<units::si::plane_angle> phase;
  
public:
  explicit Periodic(
    const units::quantity<T> offsetIn,
    const units::quantity<T> amplitudeIn,
    const units::quantity<units::si::angular_frequency> omegaIn,
    const units::quantity<units::si::plane_angle> phaseIn
    ) noexcept
    : offset( offsetIn), amplitude(amplitudeIn),
      omega( omegaIn ), phase(phaseIn)
    {
      using units::si::radians;
      assert( phase <= M_PI * radians && phase >= -M_PI* radians ) ;
      
      using units::si::radians_per_second;
      assert( omega > 0 * radians_per_second );
      
      assert( amplitude.value() > 0  ) ;
    };
  
  auto operator()( const units::quantity<units::si::time> inputTime  ) const
  -> units::quantity<T>
  {
    return evaluate( inputTime ) ;
  }
  
};
  
} // namespace functions
  
} // namespace math

#endif
