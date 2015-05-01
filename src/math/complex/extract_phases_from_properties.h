//
//  extract_phases_from_properties.h
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_math_complex__extract_phases_from_properties_h
#define tat_math_complex__extract_phases_from_properties_h

#include <vector>
#include "algorithm/algorithm.h"
#include "math/complex/properties.h"

namespace math{
namespace complex{

template< typename T>
auto extract_phases_from_properties( std::vector< properties<T> > const & ps )
{
  using namespace units;
  using std::vector;
  using algorithm::transform;
  
  auto phases = vector< quantity< plane_angle > >( ps.size());

  transform( ps, phases.begin(), []( auto const p ) noexcept {
    return p.phase ;
  } );

  return phases;
}

} // namespace complex
} // namespace math

#endif
