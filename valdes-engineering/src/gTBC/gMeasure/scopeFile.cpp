//
//  scopeFile.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>

#include "math/construct/periodic_time_distribution.h"
#include "gTBC/gMeasure/scopeFile.h"
#include "gTBC/gMeasure/get_signal_from_scope_file.h"
#include "algorithm/vector/operator_overloads.h"

namespace gTBC {

namespace gMeasure {

ScopeFile::ScopeFile
(
  std::string const & label_,
  units::quantity< units::si::wavelength > const & monochorometer_lambda_,
  units::quantity< units::si::frequency > const & laser_modulation_frequency_,
  size_t const & id_number_,
  filesystem::path const & path_
)
: label( label_ ),
  monochorometer_lambda( monochorometer_lambda_ ),
  laser_modulation_frequency( laser_modulation_frequency_ ),
  id_number( id_number_ ),
  path( path_ ),
  cycles( 6 )
{
  assert( laser_modulation_frequency_.value() > 0 ) ;
  assert( monochorometer_lambda_.value() > 0 ) ;
  assert( !label_.empty() ) ;
  assert( path_.has_filename() ) ;
  assert( path.has_extension() ) ;
  assert( cycles > 0 );
}
  
auto
ScopeFile::read_transient_signal( void )
const noexcept -> std::vector< units::quantity<units::si::electric_potential >>
{
  auto const transient_DetectorSignal =
  get_signal_from_scope_file( path );
  
  assert( 2049 ==  transient_DetectorSignal.size() );
  
  return transient_DetectorSignal;
}
  
auto
ScopeFile::readMeasurements
(
  units::quantity<units::si::electric_potential, double > const & DC_Signal
)
const noexcept -> thermal::equipment::detector::Measurements
{
  using thermal::equipment::detector::Measurements;
  using math::construct::periodic_time_distribution;
  
  auto const transient_DetectorSignal = read_transient_signal();

  auto const total_detectorSignal = DC_Signal + transient_DetectorSignal;

  auto const counts = transient_DetectorSignal.size();

  auto const referenceTime =
  periodic_time_distribution( laser_modulation_frequency, cycles, counts ) ;
  
  auto const detectorMeasurements =
  Measurements{ monochorometer_lambda, referenceTime, total_detectorSignal };
  
  return detectorMeasurements;
}
  
  
  

  
} // namespace gMeasure
  
} // namespace gTBC
