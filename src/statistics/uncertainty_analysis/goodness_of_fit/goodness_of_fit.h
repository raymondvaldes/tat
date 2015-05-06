//
//  goodness_of_fit.h
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_statistis_uncertaintyAnalysis_goodness_of_fit_h
#define tat_statistis_uncertaintyAnalysis_goodness_of_fit_h

#include <vector>
#include "units.h"
#include "statistics/signal_processing/variance/sample_variance.h"

namespace statistics{
namespace uncertainty_analysis{

template< typename T >
auto goodness_of_fit
(
  std::vector< units::quantity< T > > const & observations,
  std::vector< units::quantity< T > > const & predictions
) noexcept
{
  using signal_processing::sample_variance;
  
  auto const sv = sample_variance( observations, predictions );
  return sv.value();
}

}
}

#endif
