//
//  fit_a_b1_b2_RC.h
//  tat
//
//  Created by Raymond Valdes on 9/8/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_a_b1RC_h_090815
#define fit_a_b1RC_h_090815

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_a_b1_RC/fit_all/fit.hpp"
#include <vector>
#include <cassert>
#include "algorithm/algorithm.h"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace sept4{

inline auto fit_a_b1_RC
(
  std::vector< thermal::experimental::observations::Slab > const & specimens
) noexcept -> void
{
  assert( !specimens.empty() );

  using algorithm::for_each;
  namespace estimate_parameters =
  thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_a_b1_RC;

  for_each( specimens, []( auto const & specimen ) noexcept
  {
    auto const bestFit_results = estimate_parameters::fit_all::fit(
      specimen ) ;
    
    bestFit_results.plot_model_phases_against_observations();
  } );
  
}

} // namespace sept4
} // namespace beamExpander
} // namespace bulkDiffusivityMeasurements2015
} // namespace investigations

#endif /* fit_a_b1_b2_RC_h */
