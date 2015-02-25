//
//  vector2cstringArray.h
//  tat
//
//  Created by Raymond Valdes on 1/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__vector2cstringArray__
#define __tat__vector2cstringArray__

#include <vector>
#include <string>
#include <cassert>

#include "algorithm/algorithm.h"

namespace algorithm {

namespace vector {

inline auto string2charPtr( std::vector<std::string> const & input ) noexcept
  -> std::vector<char const *>
{
  using std::vector;
  using algorithm::transform;
  using std::begin;
  
  auto const empty = input.empty();
  auto const count = input.size();
  assert( !empty );
  
  auto const string2c_str = []( const auto& aString )
  {
    return aString.c_str();
  };

  auto output = vector< char const *>( count );
  
  transform(  input, begin( output ), string2c_str ) ;

  return output;
}

}

}
#endif /* defined(__tat__vector2cstringArray__) */
