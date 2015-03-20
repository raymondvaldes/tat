//
//  Unique_scope_measurements.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include <valarray>
#include <cmath>

#include "gTBC/gMeasure/Unique_scope_measurement.h"
#include "algorithm/algorithm.h"

#include "math/construct/periodic_time_distribution.h"
#include "algorithm/vector/operator_overloads.h"

#include "statistics/signal_processing/sum.h"
#include "statistics/signal_processing/average.h"
#include "statistics/signal_processing/signal_to_noise.h"


namespace gTBC {

namespace gMeasure {

using algorithm::transform;
using algorithm::for_each;
using std::for_each;
using units::quantity;
using units::si::electric_potential;
using std::begin;
using std::vector;
using statistics::signal_processing::signal_to_noise;
using thermal::equipment::detector::Measurements;
using math::construct::periodic_time_distribution;
  
Unique_scope_measurement::Unique_scope_measurement
(
  std::vector< ScopeFile > const & scopeFiles_
)
: scopeFiles( scopeFiles_) ,
  label( scopeFiles_.front().label ),
  monochorometer_lambda( scopeFiles_.front().monochorometer_lambda ),
  laser_modulation_frequency( scopeFiles_.front().laser_modulation_frequency ),
  size( scopeFiles_.size() ),
  cycles( scopeFiles_.front().cycles )
{
  assert( laser_modulation_frequency.value() > 0 ) ;
  assert( monochorometer_lambda.value() > 0 ) ;
  assert( !label.empty() ) ;
  
  for_each( scopeFiles, [&]( auto const & scope_file )
  {
    using std::abs;
    assert( abs(
    scope_file.monochorometer_lambda.value() -
    monochorometer_lambda.value() ) < 1e-10 ) ;
    
    assert( abs(
    scope_file.laser_modulation_frequency.value() -
    laser_modulation_frequency.value() ) < 1e-10 ) ;
  
    assert( scope_file.cycles ==  cycles ) ;
    
    assert( scope_file.label == label );
  } );
}

auto Unique_scope_measurement::reference_time( void ) const noexcept
-> std::vector< units::quantity< units::si::time > >
{
  return periodic_time_distribution( laser_modulation_frequency, cycles,counts);
}

auto Unique_scope_measurement::voltages( void ) const noexcept
-> std::vector< std::vector< units::quantity<units::si::electric_potential > > >
{
  auto signals = vector < vector < quantity < electric_potential > > >( );
  signals.reserve( scopeFiles.size( ) ) ;
  
  for_each( scopeFiles , [&]( auto const & scope_file ) noexcept
  {
    signals.emplace_back( scope_file.read_transient_signal() );
  } );
  
  return signals;
}

auto
Unique_scope_measurement::transient_measurements
(
  units::quantity< units::si::wavelength > const offset
)
const noexcept -> std::vector< thermal::equipment::detector::Measurements >
{
  auto const times = reference_time();
  auto const signals = voltages();

  auto all_measurements = vector< Measurements >();
  all_measurements.reserve( signals.size() );

  auto const lambda1 = monochorometer_lambda + offset;

  for_each( signals, [ &times, &lambda1, &all_measurements ]
  ( auto const & signal ) noexcept
  {
    auto const val = Measurements( lambda1, times, signal );
    
  //  val.plot_measurements();
    all_measurements.emplace_back( val );
  } ) ;
  
  
  assert( signals.size() == all_measurements.size() );
  
  return all_measurements;
}
  
auto
Unique_scope_measurement::transient_signal_average( void )
const noexcept -> std::vector< units::quantity<units::si::electric_potential >>
{
  auto signals = voltages();
  auto const run_vector = statistics::signal_processing::average( signals );
  
  assert( 2049 ==  run_vector.size() );
  return run_vector;
}
  
auto
Unique_scope_measurement::signal_averaged_measurement
(
  units::quantity< units::si::electric_potential, double > const DC_Signal,
  units::quantity< units::si::wavelength > const offset_monochrometer
)
const noexcept -> thermal::equipment::detector::Measurements
{
  auto const transient_DetectorSignal = transient_signal_average();
  assert( counts ==  transient_DetectorSignal.size() );

  auto const total_detectorSignal = DC_Signal + transient_DetectorSignal;
  assert( counts ==  total_detectorSignal.size() );

  auto const referenceTime = reference_time();
  auto const true_lambda = monochorometer_lambda + offset_monochrometer;
  
  auto const detectorMeasurements =
  Measurements{ true_lambda, referenceTime, total_detectorSignal };
  
  return detectorMeasurements;
}


} // namespace gMeasure

} // namespace gTBC
