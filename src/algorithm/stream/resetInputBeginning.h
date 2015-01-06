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
  
void resetToBeginnging( std::istream& inputStream ) noexcept{

  inputStream.clear();
  inputStream.seekg( 0, std::ios::beg ) ;
}

}}

#endif /* defined(__tat__resetToBeginging__) */
