//
//  read_scope_file.h
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__read_scope_file__
#define __tat__read_scope_file__

#include <string>

#include "tools/interface/filesystem.hpp"
#include "gTBC/gMeasure/scopeFile.h"

namespace gTBC {

namespace gMeasure {

auto
read_scope_file
(
  filesystem::path const & file
)
noexcept -> ScopeFile ;

} // namespace gMeasure
  
} // namespace gTBC


#endif /* defined(__tat__read_scope_file__) */

