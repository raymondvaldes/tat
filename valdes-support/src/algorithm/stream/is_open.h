//
//  is_open.h
//  tat
//
//  Created by Raymond Valdes on 1/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_is_open_h
#define tat_is_open_h

#include <fstream>

namespace algorithm {
namespace stream {

  inline auto is_open( const std::ifstream& stream ) noexcept -> bool
  {
    return stream.is_open();
  }
  
  inline auto is_closed( const std::ifstream& stream ) noexcept -> bool
  {
    return !is_open( stream );
  }

  inline auto is_open( const std::ofstream& stream ) noexcept -> bool
  {
    return stream.is_open();
  }
  
  inline auto is_closed( const std::ofstream& stream ) noexcept -> bool
  {
    return !is_open( stream );
  }

}}

#endif
