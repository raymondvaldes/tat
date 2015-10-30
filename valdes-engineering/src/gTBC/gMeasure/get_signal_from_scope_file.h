//
//  get_signal_from_scope_file.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__get_signal_from_scope_file__
#define __tat__get_signal_from_scope_file__

#include <vector>
#include <string>

#include "tools/interface/filesystem.hpp"
#include "tools/interface/import/columnData.h"
#include "units.h"

namespace gTBC {

namespace gMeasure {

auto get_signal_from_scope_file(  filesystem::directory const & dir,
                                  std::string const & inputFileName )
-> std::vector< units::quantity<units::si::electric_potential >>;

auto get_signal_from_scope_file(  filesystem::path const & path )
-> std::vector< units::quantity<units::si::electric_potential >>;
  
} // namespace gMeasure
  
} // namespace gTBC

#endif /* defined(__tat__get_signal_from_scope_file__) */
