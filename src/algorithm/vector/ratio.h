//
//  ratio.h
//  tat
//
//  Created by Raymond Valdes_New on 3/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_ratio_h
#define tat_ratio_h

#include <cassert>
#include <vector>

#include "algorithm/algorithm.h"

namespace algorithm {

namespace vector {

template< typename T >
auto ratio
(
  std::vector<T> const & numerator,
  std::vector<T> const & denominator
)
{
  using std::vector;
  auto const count = numerator.size();
  assert( count == denominator.size() );

  auto ratios =
  vector< decltype( denominator.front() / numerator.front() ) >( count );
  //ratios.reserve( count );
  
  algorithm::transform( numerator, denominator, ratios.begin(), []
  ( auto const n, auto const d ) noexcept
  {
    return n / d;
  } );
  
  assert( ratios.size() == count );
  
  return ratios;
}

  
} // namespace vector
  
} // namespace algorithm

#endif
