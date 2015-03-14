//
//  Unique_scope_measurements.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <valarray>
#include <cmath>
#include "gTBC/gMeasure/Unique_scope_measurement.h"
#include "algorithm/algorithm.h"
#include "algorithm/valarray/valarray_to_vector.h"
#include "algorithm/valarray/vector_to_valarray.h"
#include "math/construct/periodic_time_distribution.h"
#include "algorithm/vector/operator_overloads.h"


namespace gTBC {

namespace gMeasure {

using algorithm::for_each;

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


  
auto
Unique_scope_measurement::transient_signal_average( void )
const noexcept -> std::vector< units::quantity<units::si::electric_potential >>
{
  using std::valarray;
  using std::for_each;
  using alogorithm::valarray::valarray_to_vector;
  using alogorithm::valarray::vector_to_valarray;
  using algorithm::transform;
  using units::quantity;
  using units::si::dimensionless;
  using units::si::electric_potential;
  using std::begin;
  
  auto run = valarray< quantity<electric_potential> >(
    quantity<electric_potential>::from_value(0), size );
  
  for_each( scopeFiles , [&]( auto const & scope_file )
  {
    auto const current = scope_file.read_transient_signal();
    run += vector_to_valarray( current );
  });
  
  auto run_vector = valarray_to_vector( run );
  
  transform( run_vector , begin(run_vector) ,[&]( auto const & val ) {
    return val / quantity<dimensionless>( scopeFiles.size() ) ;
  });

  return run_vector;
}
  
auto
Unique_scope_measurement::signal_averaged_measurement
(
  units::quantity< units::si::electric_potential, double > const & DC_Signal,
  units::quantity< units::si::wavelength > const & offset_monochrometer
)
const noexcept -> thermal::equipment::detector::Measurements
{
  using thermal::equipment::detector::Measurements;
  using math::construct::periodic_time_distribution;
  
  auto const transient_DetectorSignal = transient_signal_average();

  auto const total_detectorSignal = DC_Signal + transient_DetectorSignal;

  auto const counts = transient_DetectorSignal.size();

  auto const referenceTime =
  periodic_time_distribution( laser_modulation_frequency, cycles, counts ) ;
  
  auto const true_lambda = monochorometer_lambda + offset_monochrometer;
  
  auto const detectorMeasurements =
  Measurements{ true_lambda, referenceTime, total_detectorSignal };
  
  return detectorMeasurements;
}


} // namespace gMeasure

} // namespace gTBC
