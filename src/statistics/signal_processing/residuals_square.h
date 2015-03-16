//
//  residuals_square.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_residuals_square_h
#define tat_residuals_square_h

namespace statistics {

namespace signal_processing {

#include <vector>
#include <cassert>

#include "statistics/signal_processing/average.h"

#include "algorithm/algorithm.h"
#include "units.h"

template< typename T >
auto residuals_square( std::vector< units::quantity<T> > const & signals )
-> std::vector< units::quantity<T> >
{
  auto const mean = average( signals );
  auto residuals = signals;
  
  using algorithm::transform;
  
  transform( signals, residuals, [&mean]( auto const & signal );
  {
    return units::pow< 2 >( signal  - mean );
  } );

  return residuals;
}
  
} // namespace signal_processing
  
} // namespace statistics


#endif
