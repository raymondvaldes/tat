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
  meta_measurement_descriptions const meta_1,
  meta_measurement_descriptions const meta_2,
  units::quantity< units::si::dimensionless> const gCoeff,
  units::quantity< units::si::electric_potential > const DC_1_offset,
  units::quantity< units::si::electric_potential > const DC_2_offset,
  thermal::pyrometry::twoColor::Set_phase set_phase
) -> Processed_tbd_files
{
  assert( gCoeff > 0 );
  assert( DC_1_offset.value() > 0 );
  assert( DC_2_offset.value() > 0 );

  if( meta_1.empty() ) { throw TBD_files_empty(); }
  if( meta_2.empty() ) { throw TBD_files_empty(); }
  if( meta_1.size() != meta_2.size() ) { throw TBD_files_do_not_match_size(); }
  
  
  auto const laser_frequencies = meta_2.laser_frequencies();
 
  auto const properties_1_raw = meta_1.measurement_periodic_signal_properties( DC_1_offset );
  auto const properties_2_raw = meta_2.measurement_periodic_signal_properties( DC_2_offset );
  

  auto phases_1 = meta_1.measurement_phases();
  auto phases_2 = meta_2.measurement_phases();


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
    properties_1, meta_1.detector_wavelength(),
    properties_2, meta_2.detector_wavelength(),
    laser_frequencies
  );
  
  
  
  return out;
};


  
} // namespace
} // namespace

