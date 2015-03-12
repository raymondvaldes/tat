//
//  scopeFiles_from_datafiles.h
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__scopeFiles_from_datafiles__
#define __tat__scopeFiles_from_datafiles__

#include <vector>

#include "tools/interface/filesystem.hpp"
#include "gTBC/gMeasure/scopeFile.h"
#include "gTBC/gMeasure/is_scope_file.h"
#include "gTBC/gMeasure/read_scope_file.h"

namespace gTBC {

namespace gMeasure {

auto
scopeFiles_from_datafiles
(
  std::vector< filesystem::path > const & dataFiles
)
noexcept -> std::vector< ScopeFile >;


} // namespace gMeasure
  
} // namespace gTBC

#endif /* defined(__tat__scopeFiles_from_datafiles__) */
