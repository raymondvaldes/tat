//
//  eof.h
//  tat
//
//  Created by Raymond Valdes on 1/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__eof__
#define __tat__eof__

#include <ios>

namespace algorithm {
namespace stream {

  
  auto eof( const std::ios& stream) noexcept -> bool
  {
    return stream.eof();
  }

  auto not_eof( const std::ios& stream ) noexcept -> bool
  {
    return !eof( stream );
  }

}}

#endif /* defined(__tat__eof__) */
