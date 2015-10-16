//
//  process_twoColor_TBD_meta_data.hpp
//  tat
//
//  Created by Raymond Valdes on 10/13/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef process_twoColor_TBD_meta_data_hpp_101315
#define process_twoColor_TBD_meta_data_hpp_101315

#include "thermal/pyrometry/twoColor/set_phase.h"
#include "gTBC/gMeasure/gTBD/meta_measurement_descriptions.hpp"
#include "gTBC/gMeasure/Processed_tbd_files.hpp"
#include "units.h"

namespace gTBC {
namespace gMeasure {

auto
process_twoColor_TBD_meta_data
(
  meta_measurement_descriptions const meta_data_1,
  meta_measurement_descriptions const meta_data_2,
  units::quantity< units::si::dimensionless> const gCoeff,
  units::quantity< units::si::electric_potential > const DC_1_offset,
  units::quantity< units::si::electric_potential > const DC_2_offset,
  thermal::pyrometry::twoColor::Set_phase set_phase
) -> Processed_tbd_files;
  
} // namespace
} // namespace

#endif /* process_twoColor_TBD_meta_data_hpp */
