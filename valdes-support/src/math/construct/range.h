//
//  range.h
//  tat
//
//  Created by Raymond Valdes on 1/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__range__
#define __tat__range__

#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstdio>

#include "algorithm/algorithm.h"
#include "units/si/si.h"

namespace math {

namespace construct {


template <class T>
auto uniform_range( T const start, T const end, size_t const points ) noexcept
{
  assert( start < end );
  using std::generate;
  using std::vector;
  using units::quantity;
  using namespace units::si;
  
  auto const span = end - start ;
  
  auto const increment = span / units::quantity<dimensionless>( points - 1 ) ;
  
  auto running_value = start ;
  
  auto myRange = vector< T >( points, start ) ;
  
  generate( myRange.begin() + 1 , myRange.end(), [running_value, &increment]()
  mutable noexcept
  {
    running_value +=  increment ;
    return running_value ;
  } );
  
  return myRange;
}

template <class T>
auto range_from_0( T const end, size_t const points ) noexcept
{
  
  auto const start = T::from_value( 0 ) ;
  
  return uniform_range( start, end , points ) ;
}

template <class T>
auto range_1og10( T const start, T const end, size_t const points )
{
  //Creates a finite uniform distribution from lmin to lmax in log10space

  using std::log10;
  using std::pow;
  using std::vector;
  
  auto output = vector< T >( points ) ;

  if( points > 2 )
  {
    auto const start_val = start.value();
    auto const start1 = log10( start_val ) + 1 ;
  
    auto const end_val = end.value();
    auto const end1   = log10( end_val ) + 1 ;
    
    auto const increments = ( end1 - start1 ) / ( points - 1 ) ;
    
    double rangeI = start1 ;

    using algorithm::generate;
    generate( output , [&]()
    {
      auto const ith_value = pow( 10, rangeI - 1 );
      rangeI += increments ;
      return T::from_value( ith_value );
    } );
    
    auto const final_value = end_val;
    output[points-1] = T::from_value( final_value ) ;
  }
  else if( points == 1 )
  {
    output[0] = start ;
  }
  else if(points == 2)
  {
    output[0] = start ;
    output[1] = end ;
  }

  return output;
}

} // namespace construct

  
} // namespace math

#endif /* defined(__tat__range__) */
