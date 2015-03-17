//
//  residuals.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_residuals_h
#define tat_residuals_h

#include <vector>

#include "units.h"
#include "statistics/signal_processing/residuals_square"

namespace statistics {

namespace sum_of_squares {

template< typename T>
auto residuals
(
  std::vector< units::quantity< T > > const & values,
  std::vector< units::quantity< T > > const & predicted
)
{
  using statistics::signal_processing::sum_residuals_square;
  
  return sum_residuals_square( values, predicted );
}
  
} // namespace sum_of_squares
  
} // namespace statistics

#endif
