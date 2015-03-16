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
  
  size_t counts = 2049;
  
  Unique_scope_measurement
  (
    std::vector< ScopeFile > const & scopeFiles_
  ) ;

  auto
  transient_signal_average( void ) const
  noexcept -> std::vector< units::quantity<units::si::electric_potential >>;
  
  auto signal_averaged_measurement
(
  units::quantity< units::si::electric_potential, double > const & DC_Signal,
  units::quantity< units::si::wavelength > const & offset
)
  const noexcept -> thermal::equipment::detector::Measurements;
  
};

} // namespace gMeasure

} // namespace gTBC

#endif /* defined(__tat__Unique_scope_measurements__) */
