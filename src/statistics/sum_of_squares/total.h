//
//  total.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_total_h
#define tat_total_h

#include <vector>

#include "units.h"
#include "statistics/signal_processing/sum_residuals_square.h"

namespace statistics {

namespace sum_of_squares {

template< typename T>
auto total( std::vector< units::quantity< T > > const & values )
{
  using statistics::signal_processing::sum_residuals_square;
  
  return sum_residuals_square( values );
}
  
} // namespace sum_of_squares
  
} // namespace statistics

#endif
