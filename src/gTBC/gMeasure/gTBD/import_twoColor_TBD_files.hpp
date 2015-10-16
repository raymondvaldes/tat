//
//  import_twoColor_TBD_files.hpp
//  tat
//
//  Created by Raymond Valdes on 10/2/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef import_twoColor_TBD_files_hpp
#define import_twoColor_TBD_files_hpp

#include <vector>
#include <string>

#include "tools/interface/filesystem.hpp"
#include "units.h"
#include "gTBC/gMeasure/Processed_tbd_files.hpp"
#include "thermal/pyrometry/twoColor/set_phase.h"


namespace gTBC {
namespace gMeasure {

auto
import_twoColor_TBD_files
(
  filesystem::path const file_lambda_1,
  filesystem::path const file_lambda_2,
  units::quantity< units::si::dimensionless> const gCoeff,
  units::quantity< units::si::electric_potential > const DC_1_offset,
  units::quantity< units::si::electric_potential > const DC_2_offset,
  thermal::pyrometry::twoColor::Set_phase set_phase
)
-> Processed_tbd_files;

} // namespace gMeasure
} // namespace gTBC

#endif /* import_twoColor_TBD_files_hpp */
