//
//  import_twoColor_scope_files.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <iostream>

#include "gTBC/gMeasure/import_twoColor_scope_files.h"
#include "gTBC/gMeasure/import_sweep_meta_data.h"

#include "gTBC/gMeasure/scopeFiles_from_datafiles.h"
#include "gTBC/gMeasure/find_unique_measurements.h"
#include "gTBC/gMeasure/unique_measurement_pair.h"
#include "gTBC/gMeasure/total_calibrated_emission_pairs.h"
#include "gTBC/gMeasure/find_unique_lambdas_in_files.h"
#include "gTBC/gMeasure/find_unique_frequencies_in_files.h"

#include "algorithm/algorithm.h"
#include "thermal/pyrometry/twoColor/pyrometery_settings_file.h"
#include <cmath>


namespace gTBC {

namespace gMeasure {

using algorithm::remove_if;

using thermal::pyrometry::twoColor::pyrometery_settings_file;
using algorithm::unique;
processed_scope_data::processed_scope_data
(
  std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > >
              const & laser_modulations_,

  std::vector<  std::pair<  thermal::equipment::detector::Measurements,
                          thermal::equipment::detector::Measurements > >
  const & measurements_,

  units::quantity< units::si::dimensionless > const & gCoefficient_
)
: laser_modulations( laser_modulations_ ),
  measurements( measurements_ ),
  gCoefficient( gCoefficient_ ) {}

auto import_twoColor_scope_files
(
  filesystem::directory const & dir,
  std::string const & filename,
  units::quantity< units::si::dimensionless> gCoeff
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
  
  auto const calibrated_emission_pairs =
  total_calibrated_emission_pairs( measurements_frequency_pairs,
    signal_DC_1,
    signal_DC_2,
    wavelength_offset
  );
  
  auto const get_meta_files = dir.ls_files( ".tbd" );
  assert( get_meta_files.size() == 1 ) ;
  
  auto const meta_data = import_sweep_meta_data( get_meta_files.front() );
  auto const laser_modulations_all = meta_data.meta_laser_modulations();
  
  auto laser_modulations =
  unique( laser_modulations_all, []( auto const &a, auto const &b )
  {
    return a.first == b.first;
  });
  
  using algorithm::any_of;
  using algorithm::remove_if;
  using std::abs;
  
  auto const new_end = remove_if( laser_modulations, [&frequencies] ( auto const a )
  {
    auto const meta_frequency = a.first;
    
    auto const is_meta_freq_in_measurement_group =
    any_of( frequencies.second, [ &meta_frequency ]( auto const b )
    {
      return (abs( b.value() - meta_frequency.value() ) < 1e-3) ;
    } ) ;
    return !is_meta_freq_in_measurement_group;
  } );
  laser_modulations.erase(new_end, laser_modulations.end());
  
  assert( laser_modulations.size() == calibrated_emission_pairs.size() );
  auto const out =  processed_scope_data(
  laser_modulations , calibrated_emission_pairs, gCoeff );
  
  return  out;
}
  
} // namespace gMeasure
  
} // namespace gTBC
