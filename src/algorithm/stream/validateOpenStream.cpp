//
//  validateOpenStream.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "algorithm/stream/validateOpenStream.h"
#include <stdexcept>

#include "algorithm/stream/is_open.h"

namespace algorithm {

namespace stream {

using std::invalid_argument;

auto validation = []( auto const & stream )
{
  const bool throwException = is_closed( stream ) ;
  
  if( throwException ) {
    throw invalid_argument( "no file found" ) ;
  }
};

auto validateOpenFile( std::ifstream const & stream ) -> void
{
  validation(stream);
}

auto validateOpenFile( std::ofstream const & stream ) -> void
{
  validation(stream);
}

} // namespace stream

} // namespace algorithm
