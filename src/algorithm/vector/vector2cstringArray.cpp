//
//  vector2cstringArray.cpp
//  tat
//
//  Created by Raymond Valdes on 1/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>      // assert


#include "algorithm/vector/vector2cstringArray.h"
#include "algorithm/algorithm.h"

namespace algorithm {

namespace vector {

auto string2charPtr( std::vector<std::string> const & inputVector ) noexcept
  -> std::vector<char const *>
{
  using std::vector;

  auto const empty = inputVector.empty();
  assert( !empty );
  
  auto const string2c_str = []( const auto& aString )
  {
    return aString.c_str();
  };

  auto outputVector = vector< char const *>( inputVector.size() );
  
  algorithm::transform(  inputVector, outputVector.begin(), string2c_str ) ;

  return outputVector;
}

} // namespace vector

} // namespace algorithm
