//
//  find_unique_labels_in_files.h
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__find_unique_labels_in_files__
#define __tat__find_unique_labels_in_files__

#include <vector>
#include <utility>

#include "gTBC/gMeasure/scopeFile.h"

namespace gTBC {

namespace gMeasure {

auto
find_unique_labels_in_files
(
  std::vector< ScopeFile > const & scope_files
)
noexcept -> std::pair< std::vector< ScopeFile >, std::vector< std::string > >;


} // namespace gMeasure
  
} // namespace gTBC
#endif /* defined(__tat__find_unique_labels_in_files__) */