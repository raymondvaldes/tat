//
//  add.h
//  tat
//
//  Created by Raymond Valdes on 9/11/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__add__
#define __tat__add__

#include <vector>
#include <algorithm>    // std::transform
#include <functional>   // std::plus

namespace algorithm {
namespace vector{


template< typename T >
decltype( auto )
add( const std::vector<T>& firstvec, const std::vector<T>& secondvec)
noexcept
{
  using std::vector;
  using std::plus;
  using std::transform;
  
  const auto vectorSize = firstvec.size();
  BOOST_ASSERT( vectorSize > 0 ) ;
  BOOST_ASSERT( vectorSize == secondvec.size() );
  
  vector<T> result( vectorSize ) ;
  
  transform( firstvec.begin(), firstvec.end(),
             secondvec.begin(),
             result.begin(), plus<double>());

  return result;
}


}}


#endif /* defined(__tat__add__) */
