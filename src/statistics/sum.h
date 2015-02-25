//
//  sum.h
//  tat
//
//  Created by Raymond Valdes_New on 2/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_sum_h
#define tat_sum_h

#include <vector>
#include "algorithm/algorithm.h"

template< Element >
auto sum( std::vector<Element> const & list ) noexcept
-> std::vector< Element >
{
  using algorithm::accumulate;
  
  auto const initial = Element();
  auto const total = accumulate( list,  initial ) ;
  
  return total;
}

#endif
