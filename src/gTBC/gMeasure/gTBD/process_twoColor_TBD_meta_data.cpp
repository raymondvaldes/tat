//
//  process_twoColor_TBD_meta_data.cpp
//  tat
//
//  Created by Raymond Valdes on 10/13/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "process_twoColor_TBD_meta_data.hpp"
#include "cout/vector/print.h"
#include "import_twoColor_TBD_files.hpp"
#include "algorithm/algorithm.h"
#include "math/functions/PeriodicProperties_update_phases.h"

namespace gTBC {
namespace gMeasure {

using math::functions::PeriodicProperties_update_phases;
using namespace units;

auto
process_twoColor_TBD_meta_data
(
  meta_measurement_descriptions const meta_data_1,
  meta_measurement_descriptions const meta_data_2,
  units::quantity< units::si::dimensionless> const gCoeff,
  units::quantity< units::si::electric_potential > const DC_1_offset,
  units::quantity< units::si::electric_potential > const DC_2_offset,
  thermal::pyrometry::twoColor::Set_phase set_phase
) -> Processed_tbd_files
{
  assert( gCoeff > 0 );
  assert( DC_1_offset.value() > 0 );
  assert( DC_2_offset.value() > 0 );
  
  assert(  meta_data_1.laser_frequencies() == meta_data_2.laser_frequencies() );
  
  auto const laser_frequencies = meta_data_2.laser_frequencies();
 
  auto const properties_1_raw = meta_data_1.measurement_periodic_signal_properties( DC_1_offset );
  auto const properties_2_raw = meta_data_2.measurement_periodic_signal_properties( DC_2_offset );
  

  auto phases_1 = meta_data_1.measurement_phases();
  auto phases_2 = meta_data_2.measurement_phases();


  switch( set_phase )
  {
    case thermal::pyrometry::twoColor::Set_phase::do_not_adjust: {
        break;
      }
    case thermal::pyrometry::twoColor::Set_phase::lambda_1: {
        phases_2 = phases_1;
        break;
      }
    case thermal::pyrometry::twoColor::Set_phase::lambda_2: {
        phases_1 = phases_2;
        break;
      }
  }
  
  auto const properties_1 = PeriodicProperties_update_phases<electric_potential>
                ( properties_1_raw, phases_1 );

  auto const properties_2 = PeriodicProperties_update_phases<electric_potential>
                ( properties_2_raw, phases_2 );
  
  auto const out = Processed_tbd_files
  (
    properties_1, meta_data_1.detector_wavelength(),
    properties_2, meta_data_2.detector_wavelength(),
    laser_frequencies
  );
  
  
  
  return out;
};


  
} // namespace
} // namespace

