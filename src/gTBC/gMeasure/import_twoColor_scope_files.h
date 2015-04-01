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

#include "thermal/equipment/detector/measurements.h"
#include "tools/interface/filesystem.hpp"
#include "units.h"

namespace gTBC {

namespace gMeasure {

struct processed_scope_data{

std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > > laser_modulations;
  
  std::vector<
  std::pair<  thermal::equipment::detector::Measurements,
              thermal::equipment::detector::Measurements > > measurements;
  
  units::quantity< units::si::dimensionless > gCoefficient;
  units::quantity< units::si::length > detector_view_radius;
  
  
  processed_scope_data
  (
    std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > > const & laser_modulations_,

    std::vector<  std::pair<  thermal::equipment::detector::Measurements,
                            thermal::equipment::detector::Measurements > >
    const & measurements_,
  
    units::quantity< units::si::dimensionless > const gCoefficient_,
    units::quantity< units::si::length > const detector_view_radius_
  );

};

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
