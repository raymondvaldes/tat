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
#include <algorithm>    // std::transform
#include <functional>   // std::plus

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
  
  const auto length = firstvec.size();
  BOOST_ASSERT( length == secondvec.size() );

  vector<T> result( length ) ;
  
  transform( firstvec.begin(), firstvec.end(),
             secondvec.begin(),
             result.begin(), minus<double>() );

  return result;
}
}}


#endif /* defined(__tat__subtract__) */
