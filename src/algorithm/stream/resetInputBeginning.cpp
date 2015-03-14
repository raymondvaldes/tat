//
//  resetToBeginging.cpp
//  tat
//
//  Created by Raymond Valdes on 1/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include "algorithm/stream/resetInputBeginning.h"

namespace algorithm {

namespace stream {

void resetToBeginnging( std::istream& inputStream ) noexcept
{
  inputStream.clear();
  inputStream.seekg( 0, std::ios::beg ) ;
}

} // namespace stream

} // namespace algorithm
