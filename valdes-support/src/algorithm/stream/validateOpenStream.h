//
//  validateOpenStream.h
//  tat
//
//  Created by Raymond Valdes on 1/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__validateOpenStream__
#define __tat__validateOpenStream__

#include <fstream>

namespace algorithm {

namespace stream {

auto validateOpenFile( std::ifstream const & stream ) -> void ;

auto validateOpenFile( std::ofstream const & stream ) -> void ;

} // namespace stream

} // namespace algorithm

#endif /* defined(__tat__validateOpenStream__) */
