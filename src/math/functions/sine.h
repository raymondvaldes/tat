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
    using std::sin;
  
    const auto angle = this->omega * time + this->phase ;
    return this->offset + this->amplitude * sin( angle.value() ) ;
  }
  
public:
  explicit Sine(
    const PeriodicProperties<T> inputProperties
  ) noexcept
  : Periodic<T>( inputProperties )
  {}
};

} // namespace functions

} // namespace math

#endif
