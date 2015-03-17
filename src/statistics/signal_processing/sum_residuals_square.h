//
//  sum_residuals_square.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_sum_residuals_square_h
#define tat_sum_residuals_square_h

#include <vector>
#include <cassert>

#include "statistics/signal_processing/residuals_square.h"
#include "statistics/sum.h"

#include "units.h"

namespace statistics {

namespace signal_processing {

template< typename T >
auto sum_residuals_square( std::vector< units::quantity<T> > const & signals )
{
  assert( signals.size() > 0 );
  
  auto const residuals_square_list = residuals_square( signals );
  
  auto const summation = sum( residuals_square_list ) ;

  return summation;
}
  
} // namespace signal_processing
  
} // namespace statistics

#endif
