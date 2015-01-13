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

namespace algorithm {
namespace vector {

auto vector2cstringArray( const std::vector<std::string> & myString )
  -> std::vector<char const *>;

  
  
}}
#endif /* defined(__tat__vector2cstringArray__) */
