//
//  subtract.h
//  tat
//
//  Created by Raymond Valdes on 9/11/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__subtract__
#define __tat__subtract__

#include <vector>
#include <functional>   // std::minus

#include "algorithm/algorithm.h"

namespace algorithm {

namespace vector{

template< typename T >
decltype( auto )
subtract( const std::vector<T>& firstvec, const std::vector<T>& secondvec)
noexcept
{
  using std::vector;
  using std::minus;
  using std::transform;
  
  auto const vectorSize = firstvec.size();
  BOOST_ASSERT( vectorSize > 0 ) ;
  BOOST_ASSERT( vectorSize == secondvec.size() );

  vector<T> result( vectorSize ) ;
  algorithm::transform( firstvec, secondvec,
             result.begin(), minus<double>() );

  return result;
}

} // namespace vector

} // naemspace algorithm


#endif /* defined(__tat__subtract__) */
