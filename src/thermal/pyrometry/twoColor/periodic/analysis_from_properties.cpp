//
//  analyis_from_properties.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include "thermal/pyrometry/twoColor/periodic/analysis_from_properties.h"
#include "cout/vector/print.h"

#include "thermal/equipment/detector/simulate_measurements/periodic_cosine.h"
#include "math/functions/PeriodicProperties.h"
#include "thermal/pyrometry/twoColor/periodic/transient_analysis.h"
#include "filesystem/path.h"

using namespace units;
using thermal::equipment::detector::simulate_measurements::periodic_cosine;
using std::string;
namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

auto analysis_from_properties
(
  math::functions::PeriodicProperties< units::si::electric_potential >
  const & properties_1,
  units::quantity<units::si::wavelength> const detector_wavelength_1,
  math::functions::PeriodicProperties< units::si::electric_potential >
  const & properties_2,
  units::quantity<units::si::wavelength> const detector_wavelength_2,
  units::quantity< units::si::dimensionless > const  gCoeff,
  units::quantity< units::si::frequency > const  laser_frequency,
  units::quantity< units::si::plane_angle> const laser_phase
)
noexcept -> transient_analysis_results
{
  assert( detector_wavelength_1 > 0 * meters );
  assert( detector_wavelength_2 > detector_wavelength_1 );
  assert( gCoeff > 0 );
  assert( laser_frequency > 0 * hertz );
  assert( std::isfinite( laser_phase.value() ) );
  assert( properties_1.omega == properties_2.omega );
  assert( properties_1.phase == properties_2.phase );

  auto const points = size_t( 100 );

  auto const measurements_1 =
    periodic_cosine( properties_1, detector_wavelength_1, points ) ;
  
  auto const measurements_2 =
    periodic_cosine( properties_2, detector_wavelength_2, points ) ;
  
  auto const dir = string("/Users/raymondvaldes/Dropbox/investigations/2color/august/poco_graphite/edm-3/phase2/");
  auto const file1 = string(dir + "lambda1.txt");
  auto const file2 = string(dir + "lambda2.txt");
  auto const print_1 = filesystem::path( file1 );
  auto const print_2 = filesystem::path( file2 );
//  measurements_1.plot_measurements( print_1 );
//  measurements_2.plot_measurements( print_2 );
  
  auto const results = transient_analysis(
    measurements_1,
    measurements_2,
    gCoeff,
    laser_frequency,
    laser_phase
  );

//  results.plot_normalized_SR( );
//  results.plot_normalized_SR_exp_model( string( dir + "normalizedSR.txt" ) );
  
  
  
  return results;
}

} // namespace periodic  
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal
