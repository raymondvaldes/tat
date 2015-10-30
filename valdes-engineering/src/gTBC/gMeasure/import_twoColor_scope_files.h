//
//  import_twoColor_scope_files.h
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__import_twoColor_scope_files__
#define __tat__import_twoColor_scope_files__

#include <vector>
#include <utility>
#include <string>

#include "tools/interface/filesystem.hpp"
#include "units.h"
#include "gTBC/gMeasure/processed_scope_data.hpp"

namespace gTBC {
namespace gMeasure {

auto
import_twoColor_scope_files
(
  filesystem::directory const & dir,
  std::string const & filename,
  units::quantity< units::si::dimensionless> gCoeff

)
-> processed_scope_data;

} // namespace gMeasure
} // namespace gTBC

#endif /* defined(__tat__import_twoColor_scope_files__) */
