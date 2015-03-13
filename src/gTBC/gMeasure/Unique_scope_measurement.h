//
//  Unique_scope_measurements.h
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__Unique_scope_measurements__
#define __tat__Unique_scope_measurements__

#include <string>
#include <cstddef>
#include <cmath>

#include "tools/interface/filesystem.hpp"
#include "gTBC/gMeasure/scopeFile.h"
#include "thermal/equipment/detector/Measurements.h"
#include "units.h"

namespace gTBC {

namespace gMeasure {

struct Unique_scope_measurement
{
  std::vector< ScopeFile > scopeFiles;
  
  std::string label;
  
  units::quantity< units::si::wavelength > monochorometer_lambda;
  
  units::quantity< units::si::frequency > laser_modulation_frequency;
  
  size_t size;
  
  size_t cycles;
  
  Unique_scope_measurement
  (
    std::vector< ScopeFile > scopeFiles_
  ) ;
  
  auto export_signal_averaged_measurement( void ) -> void ;
  
  auto signal_averaged_measurement( void ) -> void;
};

} // namespace gMeasure

} // namespace gTBC

#endif /* defined(__tat__Unique_scope_measurements__) */
