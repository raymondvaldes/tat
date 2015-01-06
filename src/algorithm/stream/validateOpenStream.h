//
//  validateOpenStream.h
//  tat
//
//  Created by Raymond Valdes on 1/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__validateOpenStream__
#define __tat__validateOpenStream__

#include "algorithm/stream/is_open.h"
#include <stdexcept>

namespace algorithm {
namespace stream {

  auto validation = [](const auto& stream )-> void
  {
    const bool throwException = is_closed( stream ) ;
    
    if( throwException ) {
      using std::invalid_argument;
      throw invalid_argument( "no file found" ) ;
    }
  };

  auto validateOpenFile( const std::ifstream& stream ) -> void
  {
    validation(stream);
  }

  auto validateOpenFile( const std::ofstream& stream ) -> void
  {
    validation(stream);
  }

}}

#endif /* defined(__tat__validateOpenStream__) */
