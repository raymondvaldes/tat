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
#include "gTBC/gMeasure/remove_grnd_if_not_in_scope_files.h"

#include "algorithm/algorithm.h"
#include "thermal/pyrometry/twoColor/pyrometery_settings_file.h"
#include <cmath>

using std::vector;
using std::abs;
using thermal::pyrometry::twoColor::pyrometery_settings_file;
using algorithm::unique;
using algorithm::remove_if;
using algorithm::any_of;
using algorithm::for_each;
using algorithm::transform;

namespace gTBC {

namespace gMeasure {

processed_scope_data::processed_scope_data
(
  std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > >
              const & laser_modulations_,

  std::vector<  std::pair<  thermal::equipment::detector::Measurements,
                          thermal::equipment::detector::Measurements > >
  const & measurements_,

  units::quantity< units::si::dimensionless > const gCoefficient_,
  units::quantity< units::si::length > const detector_view_radius_
)
: laser_modulations( laser_modulations_ ),
  measurements( measurements_ ),
  gCoefficient( gCoefficient_ ),
  detector_view_radius( detector_view_radius_ ) {}

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
  
  
  auto const get_meta_files = dir.ls_files( ".tbd" );
  assert( get_meta_files.size() == 1 ) ;
  
  auto const meta_data = import_sweep_meta_data( get_meta_files.front() );
//  auto signal_grnds = meta_data.meta_detector_grnds();
//  signal_grnds = remove_grnd_if_not_in_scope_files(signal_grnds, frequencies.second);
 
  auto const import = pyrometery_settings_file( dir.abs( filename ) );
  auto const detector_view_r = import.detector_view_radius;
  auto const signalBackground = import.signalBackground;
  auto const wavelength_offset = import.wavelength_offset ;
  
  auto signal_grnds = vector< frequency_detector_ground >();
  signal_grnds.reserve( frequencies.second.size() ) ;
  auto const lambda1_grnd = import.signal_DC_1 ;
  auto const lambda2_grnd = import.signal_DC_2 ;
  
  for_each( frequencies.second, [&signal_grnds, &lambda1_grnd, &lambda2_grnd ]
  ( auto const& freq ) noexcept
  {
    signal_grnds.push_back( {freq, lambda1_grnd, lambda2_grnd} );
  });

  auto const calibrated_emission_pairs =
  total_calibrated_emission_pairs(
    measurements_frequency_pairs,
    signalBackground,
    wavelength_offset,
    signal_grnds
  );
  

  auto const laser_modulations_all = meta_data.meta_laser_modulations();
  
  auto laser_modulations =
  unique( laser_modulations_all, []( auto const &a, auto const &b )
  {
    return a.first == b.first;
  });
  

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
  laser_modulations , calibrated_emission_pairs, gCoeff, detector_view_r );
  
  return  out;
}
  
} // namespace gMeasure
  
} // namespace gTBC
