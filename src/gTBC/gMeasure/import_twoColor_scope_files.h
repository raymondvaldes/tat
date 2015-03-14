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

#include "thermal/equipment/detector/measurements.h"
#include "tools/interface/filesystem.hpp"
#include "units.h"

namespace gTBC {

namespace gMeasure {

struct processed_scope_data{

  std::vector< units::quantity< units::si::frequency > > laser_modulation_freq;

  std::vector<
  std::pair<  thermal::equipment::detector::Measurements,
              thermal::equipment::detector::Measurements > > measurements;
  
  units::quantity< units::si::dimensionless > gCoefficient;
  
  processed_scope_data
  (
    std::vector< units::quantity< units::si::frequency > >
    const & laser_modulation_freq_,

    std::vector<  std::pair<  thermal::equipment::detector::Measurements,
                            thermal::equipment::detector::Measurements > >
    const & measurements_,
  
    units::quantity< units::si::dimensionless > const & gCoefficient_
  );

};

auto import_twoColor_scope_files( filesystem::directory const & dir )
-> processed_scope_data;

} // namespace gMeasure
  
} // namespace gTBC
#endif /* defined(__tat__import_twoColor_scope_files__) */
