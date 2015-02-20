//
//  resetToBeginging.h
//  tat
//
//  Created by Raymond Valdes on 1/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__resetToBeginging__
#define __tat__resetToBeginging__

#include <istream>
#include <iostream>

namespace algorithm {
namespace stream {
  
inline void clear( std::istream& inputStream) noexcept {
  inputStream.clear();
}

inline void seekBeginning_of_file( std::istream& inputStream) noexcept {
  inputStream.seekg( 0, std::ios::beg ) ;
}

inline void resetStreamToBeginnging( std::istream& inputStream ) noexcept{
  clear(inputStream);
  seekBeginning_of_file(inputStream);
}

}}

#endif /* defined(__tat__resetToBeginging__) */
