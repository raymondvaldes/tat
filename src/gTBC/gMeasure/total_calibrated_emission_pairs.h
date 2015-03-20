//
//  total_calibrated_emission_pairs.h
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__total_calibrated_emission_pairs__
#define __tat__total_calibrated_emission_pairs__

#include <utility>
#include <vector>

#include "gTBC/gMeasure/import_sweep_meta_data.h"
#include "gTBC/gMeasure/Unique_scope_measurement.h"
#include "thermal/equipment/detector/Measurements.h"
#include "units.h"

namespace gTBC {
  
namespace gMeasure {

auto total_calibrated_emission_pairs
(
  std::vector<
  std::pair<  Unique_scope_measurement,
              Unique_scope_measurement > > const & unique_measurements,
  std::pair<  units::quantity< units::si::wavelength>,
              units::quantity< units::si::electric_potential > > const & lambda1,
  std::pair<  units::quantity< units::si::wavelength>,
              units::quantity< units::si::electric_potential > > const & lambda2,
  units::quantity< units::si::electric_potential >  const & signal_background, 
  units::quantity< units::si::wavelength > const & offset,
  std::vector < frequency_detector_ground > const & detector_grnds
)
noexcept -> std::vector< std::pair< thermal::equipment::detector::Measurements,
                                    thermal::equipment::detector::Measurements > >;

  
  //  std::pair< lambda1, DC_offset >,
//  std::pair< lambda2, DC_offset >,
//  wavelength_offset
  
  
} // namespace gMeasure
  
} // namespace gTBC

#endif /* defined(__tat__total_calibrated_emission_pairs__) */
