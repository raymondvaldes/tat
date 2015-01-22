//
//  vector2cstringArray.cpp
//  tat
//
//  Created by Raymond Valdes on 1/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "algorithm/vector/vector2cstringArray.h"
#include <cassert>      // assert
#include <algorithm>    // std::generate

namespace algorithm {
namespace vector {



auto vector2cstringArray( const std::vector<std::string> & inputVector )
  -> std::vector<char const *>
{
  using std::vector;
  using std::transform;

  const auto vectorSize = inputVector.size();
  const auto atLeastSingleString = vectorSize > 0 ;
  assert( atLeastSingleString );
  

  const auto string2c_str = []( const auto& aString )
  { return aString.c_str(); };

  auto outputVector = vector< char const *>( vectorSize );
  
  transform(  inputVector.begin(), inputVector.end(),
              outputVector.begin(), string2c_str ) ;

  return outputVector;
}

}}
