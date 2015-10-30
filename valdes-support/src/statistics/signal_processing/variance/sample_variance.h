//
//  sample_variance.h
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_statistics_signal_processing_variance_sample_variance__
#define __tat_statistics_signal_processing_variance_sample_variance__

#include <vector>
#include <cassert>

#include "units.h"
#include "statistics/signal_processing/sum_residuals_square.h"
#include "algorithm/algorithm.h"

namespace statistics {
namespace signal_processing {

template< typename T >
auto sample_variance
(
  std::vector< T > const & observations,
  std::vector< T > const & model
)
{
  using algorithm::for_each;
  using namespace units;
  assert( observations.size() == model.size() );
  assert( !model.empty() );
  for_each( model , []( auto const e ){ assert( isfinite( e ) ); } );
  for_each( observations , []( auto const e ){ assert( isfinite( e ) ); } );

  auto const SS_residuals = sum_residuals_square( observations, model );
  auto const count = observations.size();
  
  auto const v = SS_residuals / count ;

  return v;
}




}
}
#endif /* defined(__tat__sample_variance__) */
