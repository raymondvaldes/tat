//
//  stdVector2ublasVector.cpp
//  tat
//
//  Created by Raymond Valdes on 9/11/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "algorithm/vector/stdVector2ublasVector.h"
#include <boost/assert.hpp>
#include <algorithm>

namespace algorithm {
namespace vector{

boost::numeric::ublas::vector<double>
stdVector2ublasVector( const std::vector<double>& input ) noexcept {

  using boost::numeric::ublas::vector;
  using std::copy;
  
  vector<double> output( input.size() );
  
  copy(input.begin(), input.end(), output.begin());

  return output;
}


}}
