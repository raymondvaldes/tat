//
//  sum.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_sum_h
#define tat_sum_h

#include <cassert>
#include <vector>
#include <functional>
#include <initializer_list>

#include "algorithm/algorithm.h"
#include "units.h"

namespace statistics {

namespace signal_processing {

template< typename T>
auto sum( std::vector< std::vector< units::quantity< T > > > const & signals )
noexcept -> std::vector< units::quantity< T > >
{
  using algorithm::for_each;
  using algorithm::transform;
  using units::quantity;
  using std::vector;
  using std::plus;
  
  auto const signal_size = signals.front().size();
  
  //assert that the length of each of the vectors is the same
  auto summation = vector< quantity<T> >( signal_size, quantity<T>::from_value(0) ) ;
  
  for_each( signals, [&signal_size, &summation]( auto const & signal ) noexcept
  {
    assert( signal.size() == signal_size );
    
    transform( signal.begin(), signal.end(), summation.begin(),
    summation.begin() , plus<quantity<T>>() );
  });

  return summation;
}

template< typename T >
auto sum( std::vector< T > const & list ) noexcept
{
  using algorithm::accumulate;
  
  auto const initial = list.front();
  auto const total = accumulate( list.begin()+1, list.end(),  initial ) ;
  
  return total;
}

template< typename T >
auto sum( std::initializer_list< T > const & list ) noexcept
{
  using std::accumulate;
  using std::begin;
  using std::end;

  auto const initial = *begin(list);
  auto const total = accumulate( begin(list)+1, end(list),  initial ) ;
  
  return total;
}

} // namespace signal_processing
  
} // namespace statistics

#endif
