//
//  vector.h
//  tat
//
//  Created by Raymond Valdes_New on 2/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_vector_h
#define tat_vector_h

#include <vector>
#include "units/quantity.h"
#include "units/si/predefined.h"
#include "algorithm/algorithm.h"

namespace units {

namespace si {

template< typename T >
auto
operator+ ( std::vector< T > const & list, T const & scalar) noexcept
-> std::vector< T >
{
  using algorithm::transform;
  
  auto const add_elements = [&scalar]( auto const & val ) noexcept {
    return val + scalar;
  } ;
  
  auto lhs = list;
  transform( lhs, lhs.begin(), add_elements ) ;

  return lhs;
}

template< typename T >
auto
operator+ ( T const & scalar, std::vector< T > const & list ) noexcept
-> std::vector< T >
{
  return list + scalar;
}

template< typename T >
auto
operator+= ( std::vector< T > const & list ,  T const & scalar) noexcept
-> std::vector< T >
{
  return list + scalar;
}


template< typename T >
auto
operator- ( std::vector< T > const & list, T const & scalar) noexcept
-> std::vector< T >
{
  using algorithm::transform;
  
  auto const subtract_elements = [&scalar]( auto const & val ) noexcept {
    return val - scalar;
  } ;
  
  auto lhs = list;
  transform( lhs, lhs.begin(), subtract_elements ) ;

  return lhs;
}

template< typename T >
auto
operator- ( T const & scalar, std::vector< T > const & list ) noexcept
-> std::vector< T >
{
  return list + scalar;
}

template< typename T >
auto
operator-= ( std::vector< T > const & list ,  T const & scalar) noexcept
-> std::vector< T >
{
  return list + scalar;
}

} // namespace si
  
} // namespace units

#endif
