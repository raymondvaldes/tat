//
//  vector2cstringArray.cpp
//  tat
//
//  Created by Raymond Valdes on 1/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "algorithm/vector/vector2cstringArray.h"


namespace algorithm {
namespace vector {

auto vector2cstringArray( const std::vector<std::string> & myString )
  -> std::vector<char const *>
{

  std::vector<char const *> vec2;
  vec2.reserve( myString.size() );
  
  for (auto const & str : myString ) {
    vec2.push_back( str.c_str() );
  }
  
  return vec2;
}

}}
