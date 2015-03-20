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

  units::quantity< units::si::electric_potential >  const & signal_background,
  units::quantity< units::si::wavelength > const & offset,
  std::vector < frequency_detector_ground > const & detector_grnds
)
noexcept -> std::vector<
              std::pair<  thermal::equipment::detector::Measurements,
                          thermal::equipment::detector::Measurements > >
{
  assert( unique_measurement_pairs.size() == detector_grnds.size() );
  
  auto detector_pairs = vector< pair< Measurements, Measurements > >();
  
  size_t i = 0;
  for_each( unique_measurement_pairs, [&]( auto const & u )
  {
    auto const lambda1 = detector_grnds[i].lambda1_grnd.first;
    auto const lambda2 = detector_grnds[i].lambda2_grnd.first;
  
    assert( lambda1.value() < lambda2.value() );
    
    auto const DC_signal_1 = detector_grnds[i].lambda1_grnd.second ;
    auto const DC_signal_2 = detector_grnds[i].lambda2_grnd.second ;
    
    auto const background = signal_background;
    
    auto const DC_offset_1 = DC_signal_1 - background;
    auto const DC_offset_2 = DC_signal_2 - background;
  
    assert( DC_offset_1.value() > 0 );
    assert( DC_offset_2.value() > 0 ) ;
  
    auto const first = u.first.signal_averaged_measurement( DC_offset_1 , offset );
    auto const second = u.second.signal_averaged_measurement( DC_offset_2 , offset );
  
    detector_pairs.push_back( make_pair( first, second ) ) ;
    
    ++i;
  } );
  
  return detector_pairs;
}

} // namespace gMeasure
  
} // namespace gTBC
