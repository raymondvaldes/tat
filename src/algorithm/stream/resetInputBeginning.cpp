//
//  resetToBeginging.cpp
//  tat
//
//  Created by Raymond Valdes on 1/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "algorithm/stream/resetInputBeginning.h"

namespace algorithm {
namespace stream {


std::istream resetToBeginnging( const std::istream& inputStream ) noexcept {



  inputStream.clear();
  inputStream.seekg( 0, std::ios::beg ) ;

  return inputStream;
}

  
}}