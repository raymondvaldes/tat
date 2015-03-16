//
//  signal_to_noise.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_signal_to_noise_h
#define tat_signal_to_noise_h

#include <vector>
#include <cassert>

#include "statistics/signal_processing/average.h"
#include "statistics/signal_processing/corrected_sample/standard_deviation.h"
#include "units.h"

namespace statistics {

namespace signal_to_noise {

template< typename T >
auto
signal_to_noise( std::vector< units::quantity< T > > const & signals )
-> units::quantity< units::si::dimensionless>
{
  assert( signals.size() > 0 );
  
  using corrected_sample::standard_deviation;
  
  auto const mean = average( signals );
  auto const std_deviation = standard_deviation( signals ) ;

  auto const SNR = mean / std_deviation;

  return SNR
}

  
} // namespace signal_to_noise
  
} // namespace statistics

#endif
