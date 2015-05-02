//
//  extract_amplitudes_from_phases.h
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_math_complex_extract_amplitudes_from_phases_h
#define tat_math_complex_extract_amplitudes_from_phases_h

#include <vector>
#include "algorithm/algorithm.h"
#include "math/complex/properties.h"

namespace math{
namespace complex{

template< typename T>
auto extract_amplitudes_from_properties( std::vector< properties<T> > const & ps )
{
  using namespace units;
  using std::vector;
  using algorithm::transform;
  
  auto amplitudes = vector< quantity< T > >( ps.size());

  transform( ps, amplitudes.begin(), []( auto const & p ) noexcept {
    return p.amplitude ;
  } );

  return amplitudes;
}

} // namespace complex
} // namespace math

#endif
