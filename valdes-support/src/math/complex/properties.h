//
//  properties.h
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_math_complex_properties__
#define __tat_math_complex_properties__

#include "units.h"
#include <cassert>
#include <cmath>

namespace math{
namespace complex{

template< typename T >
struct properties{

  units::quantity< units::si::plane_angle, double > phase;
  units::quantity< T, double > amplitude;

  explicit properties(){} 

  explicit properties
  (
    units::quantity< units::si::plane_angle > const phase_,
    units::quantity< T > const amplitude_
  ) noexcept :
    phase( phase_),
    amplitude( amplitude_ )
  {
    assert( isfinite( phase ) );
    assert( amplitude.value() > 0 );
  }
  
  auto complex_value() const
  {
    auto const phase_value = phase.value();
    auto const amplitude_value = amplitude.value();
   
    using std::exp;
    auto const i = std::complex<double>( 0.0 , 1.0 );
    
    auto const cv = amplitude_value * exp( i * phase_value );
    return cv;
  }
};

} // namespace complex
} // namespace math

#endif /* defined(__tat__properties__) */
