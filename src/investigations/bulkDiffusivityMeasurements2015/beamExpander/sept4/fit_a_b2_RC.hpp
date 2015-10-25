//
//  fit_a_b1_b2_RC.h
//  tat
//
//  Created by Raymond Valdes on 9/8/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_a_b2_RC_h_090815_q2345q345
#define fit_a_b2_RC_h_090815_q2345q345

#include "units.h"
#include <cassert>

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_a_b2_RC/fit_all/fit.hpp"
#include <vector>
#include "algorithm/algorithm.h"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace sept4{

inline auto fit_a_b2_RC
(
  std::vector< thermal::experimental::observations::Slab > const & specimens, 
  units::quantity<  units::si::length > const detector_offset
) noexcept -> void
{
  assert( !specimens.empty() );
  assert( detector_offset.value() > 0 );
  
  using algorithm::for_each;
  namespace estimate_parameters =
  thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_a_b2_RC;


  for_each( specimens, [ detector_offset ]( auto const & specimen ) noexcept
  {
    estimate_parameters::fit_all::fit(
      specimen, detector_offset ) ;
    
//    bestFit_results.plot_model_phases_against_observations();
  } );
  
}

} // namespace sept4
} // namespace beamExpander
} // namespace bulkDiffusivityMeasurements2015
} // namespace investigations

#endif /* fit_a_b1_b2_RC_h */
