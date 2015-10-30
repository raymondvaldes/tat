//
//  standard_deviation.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_standard_deviation_h
#define tat_standard_deviation_h

#include <vector>

#include "statistics/signal_processing/corrected_sample/variance.h"
#include "units.h"

namespace statistics {

namespace signal_processing {

namespace corrected_sample  {

template< typename T >
auto standard_deviation( std::vector< units::quantity<T> > const & signals )
-> units::quantity<T>
{
  using units::sqrt;

  auto const myVariance = unbiased_variance( signals );
  auto const myStandard_deviation = sqrt( myVariance ) ;

  return myStandard_deviation;
}

} // namespace standard_deviation
  
} // namespace signal_processing
  
} // namespace statistics

#endif
