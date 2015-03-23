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
#include <initializer_list>

#include "algorithm/algorithm.h"
#include "statistics/signal_processing/sum.h"
#include "statistics/signal_processing/divide_each_element.h"
#include "units.h"

namespace statistics {

namespace signal_processing {

template< typename T >
auto average( std::vector< std::vector< units::quantity< T > > > const & signals )
noexcept -> std::vector< units::quantity< T > >
{
  using algorithm::for_each;
  
  //assert that the length of each of the vectors is the same
  assert( signals.size() > 0 );
  auto const each_signal_size = signals.front().size();
  
  assert( each_signal_size > 0 );

  for_each( signals, [&each_signal_size]( auto const & signal ){
    assert( signal.size() == each_signal_size );
  });
  
  auto const sums = sum( signals ) ;
  auto const average_out = divide_each_element( sums , signals.size() );

  return average_out;
}

template< typename T >
auto average( std::vector< units::quantity< T > > const & signals )
noexcept -> units::quantity<T>
{
  using units::quantity;
  using units::si::dimensionless;
  
  auto const signal_size = signals.size();
  assert( signal_size > 0 ) ;

  auto const sums = sum( signals ) ;
  auto const count = quantity< dimensionless >( signal_size );
  auto const mean = sums / count ;

  return mean;
}

template< typename T >
auto average( std::initializer_list< units::quantity< T > > const & list )
{
  using namespace units;
  
  auto const sum_of_list = sum( list );
  auto const count = quantity< dimensionless >( list.size() );
  
  auto const average_value = sum_of_list / count;
  
  return average_value;
}

} // namespace signal_processing
  
} // namespace statistics

#endif
