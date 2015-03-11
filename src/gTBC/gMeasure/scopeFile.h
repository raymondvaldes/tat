//
//  scopeFile.h
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_scopeFile_h
#define tat_scopeFile_h

#include <string>
#include <cstddef>

#include "tools/interface/filesystem.hpp"
#include "units.h"

namespace gTBC {

namespace gMeasure {

struct ScopeFile
{
  std::string label;
  
  units::quantity< units::si::wavelength > monochorometer_lambda;
  
  units::quantity< units::si::frequency > laser_modulation_frequency;
  
  size_t id_number;
  
  filesystem::path path;
  
  ScopeFile
  (
    std::string const & label_,
    units::quantity< units::si::wavelength > const & monochorometer_lambda_,
    units::quantity< units::si::frequency > const & laser_modulation_frequency_,
    size_t const & id_number_,
    filesystem::path const & path_
  );
};
  
} // namespace gMeasure
  
} // namespace gTBC

#endif
