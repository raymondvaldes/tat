//
//  sum_residuals_square.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_statistics_signal_processing_sum_residuals_square_h
#define tat_statistics_signal_processing_sum_residuals_square_h

#include <vector>
#include <cassert>
#include <cmath>

#include "statistics/signal_processing/residuals_square.h"
#include "statistics/signal_processing/sum.h"
#include "units.h"
#include "algorithm/algorithm.h"

namespace statistics {
namespace signal_processing {

template< typename T >
auto sum_residuals_square
(
  std::vector< T > const & observations /* observations*/,
  std::vector< T > const & model /*model*/
)
{
  using algorithm::for_each;
  using std::isfinite;
  
  assert( observations.size() == model.size() ) ;
  assert( !observations.empty() );
  for_each( model , []( auto const e ){ assert( isfinite( e ) ); } );
  for_each( observations , []( auto const e ){ assert( isfinite( e ) ); } );

  
  auto const residuals_square_list = residuals_square( observations, model );
  auto const summation = sum( residuals_square_list ) ;

  return summation;
}

} // namespace signal_processing
} // namespace statistics

#endif
