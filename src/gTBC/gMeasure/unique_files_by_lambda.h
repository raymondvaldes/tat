//
//  unique_files_by_lambda.h
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__unique_files_by_lambda__
#define __tat__unique_files_by_lambda__

#include <vector>
#include "gTBC/gMeasure/scopeFile.h"

namespace gTBC {

namespace gMeasure {

auto
unique_files_by_lambda
(
  std::vector< ScopeFile > const & sorted_files
)
noexcept -> std::vector< ScopeFile >;

} // namespace gMeasure
  
} // namespace gTBC
#endif /* defined(__tat__unique_files_by_lambda__) */
