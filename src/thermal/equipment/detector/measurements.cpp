//
//  measurements.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>

#include "cout/vector/print.h"
#include "thermal/equipment/detector/measurements.h"
#include "algorithm/algorithm.h"
#include "plot/gnuplot.h"
#include "math/functions/cosine.h"

namespace thermal {
namespace equipment {
namespace detector {

using std::vector;
using units::quantity;
using units::si::time;
using units::si::electric_potential;
using algorithm::generate;
using algorithm::transform;
using units::container::quantityTodouble;

Measurements::Measurements(
  units::quantity<units::si::wavelength> const wavelengthIn,
  std::vector< units::quantity< units::si::time> > const & referenceTime,
  std::vector< units::quantity< units::si::electric_potential > > const & signals )
  : measurements( signals.size() ), wavelength( wavelengthIn )
{
  assert( wavelengthIn.value() > 0 );
  assert( referenceTime.size() == signals.size() );
  for( auto const t :  referenceTime ){
    assert( std::isfinite( t.value() ) );
  }
  for( auto const s : signals ) {
    assert( std::isfinite( s.value() ) );
  }
  
  size_t i = 0u;
  generate( measurements, [&referenceTime, &signals, &i]() noexcept
  {
    auto const melissa = Measurement{ referenceTime[i], signals[i] };
    ++i;
    return melissa;
  } );
  
};

auto Measurements::delta_time( void )
const noexcept -> units::quantity< units::si::time >
{
  auto const time_ref_0 = measurements[0].reference_time;
  auto const time_ref_1 = measurements[1].reference_time;
  return time_ref_1 - time_ref_0;
}

auto Measurements::size( void )
const noexcept -> size_t
{
  return measurements.size();
};

auto Measurements::referenceTimes( void )
const noexcept-> std::vector< units::quantity<units::si::time> >
{
  auto const count = size();
  
  auto const myMeasurements = measurements;
  auto times = vector< quantity< time > >{ count };
  auto i = 0;

  generate( times, [ &myMeasurements, &i]() noexcept
  {
    auto const time = myMeasurements[i].reference_time;
    ++i;
    return time ;
  } );

  return times;
}

auto Measurements::signals_electical_potential( void )
const noexcept-> std::vector< units::quantity<units::si::electric_potential> >
{
  auto const count = size();
  
  auto const myMeasurements = measurements;
  auto signals = vector< quantity< electric_potential > >{ count };

  transform( myMeasurements, signals.begin(), []( auto const measurement ){
    auto const signal = measurement.signal;
    return signal ;
  } );
  
  return signals;
}

auto Measurements::print_table_measurements_values( void ) const noexcept -> void
{
  auto const times = referenceTimes();
  auto const signals = signals_electical_potential();
  auto const precision = 9;

  cout::vector::print_table_values( times, signals, precision );
}


auto Measurements::plot_measurements( filesystem::path const & print_file
) const noexcept -> void
{
	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  gp << "set xlabel 'time (s)'" << "\n";
  gp << "set ylabel 'detector (V)'" << "\n";
  
  auto const x_vec = referenceTimes();
  auto const y_vec = signals_electical_potential();
  
  auto const x_pts = quantityTodouble( x_vec );
  auto const y1_pts = quantityTodouble( y_vec );
    
  auto const xy1_pts = make_pair( x_pts, y1_pts );

  auto const print_file_string = print_file.string();
  
  gp << "plot"
  << gp.file1d( xy1_pts, print_file_string ) << "with points title 'thermal detector measurements',"
  << std::endl;
}

auto transient_sinusoidal_measurements_factory
(
  units::quantity< units::si::wavelength > const detector_wavelength,
  units::quantity< units::si::frequency > const periodic_frequency,
  units::quantity< units::si::plane_angle > const phase,
  units::quantity< units::si::electric_potential > const amplitude
) noexcept -> Measurements
{
  using math::functions::PeriodicProperties;
  using math::functions::Cosine;

  auto const offset = quantity<electric_potential>::from_value(0);

  auto const periodic_properties =
  PeriodicProperties< electric_potential >
  (
    offset,
    amplitude,
    periodic_frequency,
    phase
  );

  //generate detector transient signals
  auto const sinusoidal_generator =
  Cosine< electric_potential >( periodic_properties );
  
  auto const N_periods = 0;
  auto const N_values = 500;
  auto const measurements_evaluated =
  sinusoidal_generator.evaluate_for_n_periods( N_periods, N_values );
  
  auto const measurements_object =
  Measurements
  (
    detector_wavelength,
    measurements_evaluated.first,
    measurements_evaluated.second
  );
  
  
  return measurements_object;
}
  
} // namespace detector
} // namespace equipment
} // namespace thermal
