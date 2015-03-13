//
//  find_all_files_with.h
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__find_all_files_with__
#define __tat__find_all_files_with__

#include <vector>
#include <string>
#include "gTBC/gMeasure/scopeFile.h"
#include "units.h"

namespace gTBC {

namespace gMeasure{

auto find_all_files_with_label
(
  std::vector< ScopeFile > const & scope_files, std::string const & label
)
noexcept ->  std::vector< ScopeFile >;

auto find_all_files_with_lambda
(
  std::vector< ScopeFile > const & scope_files,
  units::quantity< units::si::wavelength >const & lambda
)
noexcept ->  std::vector< ScopeFile >;

auto find_all_files_with_frequency
(
  std::vector< ScopeFile > const & scope_files,
  units::quantity< units::si::frequency >const & frequency
)
noexcept ->  std::vector< ScopeFile >;

} // namespace gMeasure

} // namespace gTBC

#endif /* defined(__tat__find_all_files_with__) */
