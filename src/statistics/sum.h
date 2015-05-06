//
//  sum.h
//  tat
//
//  Created by Raymond Valdes_New on 2/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_statistics_signal_processing_sum_h
#define tat_statistics_signal_processing_sum_h

#include <vector>
#include "algorithm/algorithm.h"

#include "units.h"

template< typename T >
auto sum( std::vector< units::quantity< T > > const & list )
{
  assert( !list.empty() );
  
  using algorithm::accumulate;
  using namespace units;
  
  auto const initial = quantity<T>::from_value(0) ;
  auto const total = accumulate( list,  initial ) ;
  
  return total;
}

//template< Element >
//auto sum( std::vector<Element> const & list ) noexcept
//-> std::vector< Element >
//{
//  using algorithm::accumulate;
//  
//  auto const initial = Element();
//  auto const total = accumulate( list,  initial ) ;
//  
//  return total;
//}

#endif
