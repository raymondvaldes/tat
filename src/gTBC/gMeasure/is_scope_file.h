//
//  is_scope_file.h
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__is_scope_file__
#define __tat__is_scope_file__


#include "tools/interface/filesystem.hpp"
#include "gTBC/gMeasure/scopeFile.h"

namespace gTBC {

namespace gMeasure {

auto
is_scope_file
(
  filesystem::directory const & dir,
  std::string const & filename
) noexcept -> bool;


} // namespace gMeasure
  
} // namespace gTBC

#endif /* defined(__tat__is_scope_file__) */
