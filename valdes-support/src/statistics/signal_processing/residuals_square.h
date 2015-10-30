//
//  residuals_square.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_statistics_signal_processing_residuals_square_h
#define tat_statistics_signal_processing_residuals_square_h

#include <vector>
#include <cassert>
#include <cmath>

#include "statistics/signal_processing/residuals/residual_square.h"
#include "algorithm/algorithm.h"

namespace statistics {
namespace signal_processing {

template< typename T >
auto residuals_square
(
  std::vector< T > const & observations,
  std::vector< T > const & model
)
{
  using algorithm::for_each;
  assert( observations.size() == model.size() );
  assert( !model.empty() );
  for_each( model , []( auto const e ){ assert( isfinite( e ) ); } );
  for_each( observations , []( auto const e ){ assert( isfinite( e ) ); } );

  using std::vector;
  using algorithm::transform;

  
  auto const N = observations.size();
  auto residuals = vector< decltype( model.front() * model.front() ) >( N );
  
  transform(
  observations.begin(), observations.end(), model.begin(), residuals.begin(),
  []( auto const observation, auto const model ) noexcept
  {
    return residual_square( observation, model );
  } ) ;
  

  return residuals;
}

} // namespace signal_processing
  
} // namespace statistics

#endif
