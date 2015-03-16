//
//  import_twoColor_scope_files.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "gTBC/gMeasure/import_twoColor_scope_files.h"

#include "gTBC/gMeasure/scopeFiles_from_datafiles.h"
#include "gTBC/gMeasure/find_unique_measurements.h"
#include "gTBC/gMeasure/unique_measurement_pair.h"
#include "gTBC/gMeasure/total_calibrated_emission_pairs.h"
#include "gTBC/gMeasure/find_unique_lambdas_in_files.h"
#include "gTBC/gMeasure/find_unique_frequencies_in_files.h"

#include "thermal/pyrometry/twoColor/pyrometery_settings_file.h"

namespace gTBC {

namespace gMeasure {

using thermal::pyrometry::twoColor::pyrometery_settings_file;

processed_scope_data::processed_scope_data
(
  std::vector< units::quantity< units::si::frequency > >
  const & laser_modulation_freq_,

  std::vector<  std::pair<  thermal::equipment::detector::Measurements,
                          thermal::equipment::detector::Measurements > >
  const & measurements_,

  units::quantity< units::si::dimensionless > const & gCoefficient_
)
: laser_modulation_freq( laser_modulation_freq_ ),
  measurements( measurements_ ),
  gCoefficient( gCoefficient_ ) {}

auto import_twoColor_scope_files
(
  filesystem::directory const & dir,
  std::string const & filename
)
-> processed_scope_data
{
  auto const getDataFiles = dir.ls_files( ".dat" );
  auto const scopeFiles = scopeFiles_from_datafiles( getDataFiles ) ;
  
  auto const lambdas = find_unique_lambdas_in_files( scopeFiles ) ;
  
  auto const frequencies = find_unique_frequencies_in_files( scopeFiles ) ;
  
  auto const unique_measurements = find_unique_measurements( scopeFiles ) ;

  auto const measurements_frequency_pairs =
  unique_measurement_pairs( unique_measurements, frequencies.second );
  
  auto const import = pyrometery_settings_file( dir.abs( filename ) );
  
  auto signal_DC_1 = import.signal_DC_1 ;
  auto signal_DC_2 = import.signal_DC_2 ;
  auto const signalBackground = import.signalBackground;
  signal_DC_1.second -= signalBackground; // remove the background noise
  signal_DC_2.second -= signalBackground; // remove the background noise
  
  auto const wavelength_offset = import.wavelength_offset ;
  auto const gCoeff = import.gCoeff ;
  
  auto const calibrated_emission_pairs =
  total_calibrated_emission_pairs( measurements_frequency_pairs,
    signal_DC_1,
    signal_DC_2,
    wavelength_offset
  );
  
  auto const out =
  processed_scope_data( frequencies.second, calibrated_emission_pairs, gCoeff );
  
  return  out;
}
  
} // namespace gMeasure
  
} // namespace gTBC
