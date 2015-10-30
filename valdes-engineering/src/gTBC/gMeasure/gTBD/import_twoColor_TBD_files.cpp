//
//  import_twoColor_TBD_files.cpp
//  tat
//
//  Created by Raymond Valdes on 10/2/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include <iostream>

#include "cout/vector/print.h"
#include "import_twoColor_TBD_files.hpp"
#include "gTBC/gMeasure/import_sweep_meta_data.h"
#include "algorithm/algorithm.h"
#include "math/functions/PeriodicProperties_update_phases.h"
#include "process_twoColor_TBD_meta_data.hpp"

namespace gTBC {
namespace gMeasure {

using math::functions::PeriodicProperties_update_phases;
using namespace units;


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
-> Processed_tbd_files
{
  assert( gCoeff > 0 );
  assert( DC_1_offset.value() > 0 );
  assert( DC_2_offset.value() > 0 );
  
  auto const meta_data_1 = import_sweep_meta_data( file_lambda_1 );
  auto const meta_data_2 = import_sweep_meta_data( file_lambda_2 );
 
  assert(  meta_data_1.laser_frequencies() == meta_data_2.laser_frequencies() );
  
  auto const out = process_twoColor_TBD_meta_data(
    meta_data_1,
    meta_data_2,
    gCoeff,
    DC_1_offset, DC_2_offset, set_phase );
  
  return out;
}



} // namespace gMeasure
} // namespace gTBC

