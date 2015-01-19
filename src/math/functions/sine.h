//
//  sine.h
//  tat
//
//  Created by Raymond Valdes on 1/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_sine_h
#define tat_sine_h

#include "math/functions/periodic.h"

namespace math {
  
namespace functions {

template< typename T >
class Sine: public Periodic<T>
{
private:
  auto evaluate( const units::quantity<units::si::time> time )
  const noexcept
  -> units::quantity<T>
  {
    const auto angle = this->omega * time + this->phase ;
  
    using std::sin;
    return this->offset + this->amplitude * sin( angle.value() ) ;
  }
  
public:
  explicit Sine(
    const units::quantity<T> offsetIn,
    const units::quantity<T> amplitudeIn,
    const units::quantity<units::si::angular_frequency> omegaIn,
    const units::quantity<units::si::plane_angle> phaseIn
    ) noexcept
    : Periodic<T>( offsetIn, amplitudeIn, omegaIn , phaseIn)
    {};

};

} // namespace functions

} // namespace math

#endif
