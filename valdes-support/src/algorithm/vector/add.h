//
//  add.h
//  tat
//
//  Created by Raymond Valdes on 9/11/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__add__234123
#define __tat__add__234123

#include <vector>

#include "algorithm/algorithm.h"

namespace algorithm {
namespace vector{

template< typename T >
auto add( std::vector< T > const & firstvec, std::vector<T> const & secondvec )
noexcept
{
  using std::vector;
  using std::begin;
  
  auto const vectorSize = firstvec.size();
  BOOST_ASSERT( vectorSize > 0 ) ;
  BOOST_ASSERT( vectorSize == secondvec.size() );
  
  auto result = vector< T >( vectorSize ) ;
  
  algorithm::transform( firstvec,  secondvec, begin( result ), []
  ( auto const a, auto const b ) noexcept
  {
    return a + b ;
  } );

  return result;
}

} // namespace vector
} // namespace algorithm


#endif /* defined(__tat__add__) */
