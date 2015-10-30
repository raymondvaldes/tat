//
//  divide_each_element.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_divide_each_element_h
#define tat_divide_each_element_h

#include <vector>
#include <cstddef>

#include "algorithm/algorithm.h"
#include "units.h"

namespace statistics {

namespace signal_processing {

template< typename T>
auto divide_each_element
(
  std::vector< units::quantity< T > > const & signals ,
  size_t const denominator
)
noexcept -> std::vector< units::quantity< T > >
{
  using std::transform;
  using units::quantity;
  using units::si::dimensionless;
  using std::vector;
  
  auto const signal_size = signals.size();
  auto output = vector< quantity<T> >( signal_size, quantity<T>::from_value(0) ) ;

  transform( signals.begin(), signals.end() , output.begin(), [&denominator]
  ( auto const a )
  {
    return a / quantity< dimensionless >( denominator );
  } );

  return output;
}

} // namespace signal_processing
  
} // namespace statistics

#endif
