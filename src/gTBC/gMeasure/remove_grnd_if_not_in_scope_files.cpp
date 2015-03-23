//
//  remove_grnd_if_not_in_scope_files.cpp
//  tat
//
//  Created by Raymond Valdes on 3/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>

#include "remove_grnd_if_not_in_scope_files.h"
#include "algorithm/algorithm.h"

using algorithm::remove_if;
using algorithm::any_of;
using std::abs;

namespace gTBC {

namespace gMeasure {

auto remove_grnd_if_not_in_scope_files
(
  std::vector < frequency_detector_ground > const signal_grnds_,
  std::vector< units::quantity< units::si::frequency > > frequencies
)
noexcept -> std::vector < frequency_detector_ground >
{
  auto signal_grnds = signal_grnds_;
  
  auto const end_of_gnd =
  remove_if( signal_grnds, [&frequencies] ( auto const & a )
  {
    auto const meta_frequency = a.laser_frequency;
    
    auto const is_meta_freq_in_measurement_group =
    any_of( frequencies, [ &meta_frequency ]( auto const & b )
    {
      return (abs( b.value() - meta_frequency.value() ) < 1e-3) ;
    } ) ;
    return !is_meta_freq_in_measurement_group;
  } );
  
  signal_grnds.erase( end_of_gnd, signal_grnds.end() );
  
  assert( signal_grnds.size() == frequencies.size() );
  
  return signal_grnds;
}
  
} // namespace gMeasure
  
} // namespace gTBC