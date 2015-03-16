//
//  average.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_average_h
#define tat_average_h

#include <cassert>
#include <vector>

#include "algorithm/algorithm.h"
#include "statistics/signal_processing/sum.h"
#include "statistics/signal_processing/divide_each_element.h"
#include "units.h"

namespace statistics {

namespace signal_processing {

template< typename T >
auto average( std::vector< std::vector< units::quantity< T > > > const & signals )
noexcept -> std::vector< units::quantity<T> >
{
  using algorithm::for_each;
  
  //assert that the length of each of the vectors is the same
  assert( signals.size() > 0 );
  auto const signal_size = signals.front().size();
  assert( signal_size > 0 );
  for_each( signals, [&signal_size]( auto const & signal ){
    assert( signal.size() == signal_size );
  });
  
  auto const sums = sum( signals ) ;
  auto const average_out = divide_each_element( sums , signal_size );

  return average_out;
}

} // namespace signal_processing
  
} // namespace statistics

#endif
