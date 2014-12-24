//
//  subtract.cpp
//  tat
//
//  Created by Raymond Valdes on 9/11/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "algorithm/vector/subtract.h"
#include <boost/assert.hpp>

#include <algorithm>    // std::transform
#include <functional>   // std::plus

namespace algorithm {
namespace vector{

std::vector<double> subtract(  const std::vector<double>& firstvec,
                               const std::vector<double>& secondvec) noexcept{
  using std::transform;
  using std::minus;
  
  const size_t length = firstvec.size();
  BOOST_ASSERT( length == secondvec.size() );
  std::vector<double> result( length ) ;
  
  transform( firstvec.begin(), firstvec.end(),
             secondvec.begin(),
             result.begin(), minus<double>() ) ;

    return result;
}

}}