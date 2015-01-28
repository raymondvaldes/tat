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
#include "units/si/si.h"

namespace math {

namespace construct {


template <class T>
auto range( const T start, const T end, const size_t points ) noexcept
{
  assert( start < end );
  using std::generate;
  using std::vector;
  using units::quantity;
  using namespace units::si;
  
  const auto span = end - start ;
  
  const auto increment = span / units::quantity<dimensionless>( points - 1 ) ;
  
  
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
auto range_from_0( const T end, const size_t points ) noexcept
{
  
  const auto start = T::from_value(0) ;
  
  return range( start, end , points ) ;
}



  
} // namespace construct

  
} // namespace math

#endif /* defined(__tat__range__) */
