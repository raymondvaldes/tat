//
//  total_calibrated_emission_pairs.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>
#include "gTBC/gMeasure/total_calibrated_emission_pairs.h"
#include "algorithm/algorithm.h"

namespace gTBC {
  
namespace gMeasure {

using std::vector;
using std::pair;
using thermal::equipment::detector::Measurements;
using algorithm::for_each;
using std::make_pair;

auto total_calibrated_emission_pairs
(
  std::vector<
  std::pair<  Unique_scope_measurement,
              Unique_scope_measurement > > const & unique_measurement_pairs,
 
  std::pair<  units::quantity< units::si::wavelength>,
              units::quantity< units::si::electric_potential > > const & lambda1,
 
  std::pair<  units::quantity< units::si::wavelength>,
              units::quantity< units::si::electric_potential > > const & lambda2,
 
  units::quantity< units::si::wavelength > const & offset
)
noexcept -> std::vector<
              std::pair<  thermal::equipment::detector::Measurements,
                          thermal::equipment::detector::Measurements > >
{
  assert( lambda1.first.value() < lambda2.second.value() );
  
  auto detector_pairs = vector< pair< Measurements, Measurements > >();
  
  for_each( unique_measurement_pairs, [&]( auto const & u )
  {
    auto const DC_offset_1 = lambda1.second;
    auto const first = u.first.signal_averaged_measurement( DC_offset_1 , offset );

    auto const DC_offset_2 = lambda2.second;
    auto const second = u.second.signal_averaged_measurement( DC_offset_2 , offset );
  
    detector_pairs.push_back( make_pair( first, second ) ) ;
  } );
  
  return detector_pairs;
}

  
} // namespace gMeasure
  
} // namespace gTBC
