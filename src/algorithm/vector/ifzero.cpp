//
//  ifzero.cpp
//  tat
//
//  Created by Raymond Valdes on 9/12/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "algorithm/vector/ifzero.h"
#include <algorithm>

using std::find;

namespace algorithm {

namespace vector{

bool ifzero( const double* vec, const size_t N ) noexcept {

  const int searchParameter = 0 ;
  const bool pass = find( vec, vec + N, searchParameter ) != vec + N ;
  return pass;
}

bool if_not_zero( const double* vec, const size_t N ) noexcept {

  const bool pass = !ifzero( vec, N ) ;
  return pass;
}

bool ifzero( const std::vector<double>& vec ) noexcept {
  
  const bool pass = ifzero( vec.data(), vec.size() ) ;
  return pass;
}

bool if_not_zero( const std::vector<double>& vec ) noexcept {
  const bool pass = !ifzero( vec ) ;
  return pass;
}


}}
