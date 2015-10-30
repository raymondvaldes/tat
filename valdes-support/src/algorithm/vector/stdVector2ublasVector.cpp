//
//  stdVector2ublasVector.cpp
//  tat
//
//  Created by Raymond Valdes on 9/11/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "algorithm/vector/stdVector2ublasVector.h"
#include "algorithm/algorithm.h"

namespace algorithm {

namespace vector{

boost::numeric::ublas::vector<double>
stdVector2ublasVector( const std::vector<double>& input ) noexcept {

  using boost::numeric::ublas::vector;
  using std::copy;
  
  vector<double> output( input.size() );
  
  algorithm::copy( input, output.begin() );

  return output;
}

} // namespace vector

} // namespace algorithm
