//
//  fit_a_b1_b2_RC.h
//  tat
//
//  Created by Raymond Valdes on 9/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_a_b1_b2_RC_h_0928151
#define fit_a_b1_b2_RC_h_0928151


#include "units.h"

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_a_b1_b2_RC/fit_all/fit.hpp"
#include <vector>
#include "algorithm/algorithm.h"
#include <iostream>

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace adiabatic_rear{
namespace poco_edm3{

inline auto fit_a_b1_b2_RC
(
  std::vector< thermal::experimental::observations::Slab > const & specimens, 
  units::quantity<  units::si::length > const detector_radius
) noexcept -> void
{
  assert( !specimens.empty() );
  assert( detector_radius.value() > 0 );

  using std::cout;
  using algorithm::for_each;
  namespace estimate_parameters =
  thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_a_b1_b2_RC;


  for_each( specimens, [ detector_radius ]( auto const & specimen ) noexcept
  {
    estimate_parameters::fit_all::fit( specimen, detector_radius ) ;
    
//    bestFit_results.plot_model_phases_against_observations();
    
//    auto i = 0u;
//    for_each( bestFit_results.frequencies,
//    [ &bestFit_results, &i ]( auto const frequency ) noexcept
//    {
//      auto const model_phase = bestFit_results.model_phases[i];
//      auto const observation = bestFit_results.observations[i];
//      
//      cout << frequency.value() << "\t" << model_phase.value() << "\t" << observation.value() << "\n";
//      ++i;
//    } );
  } );
}

} // namespace poco_edm3
} // namespace adiabatic_rear
} // namespace beamExpander
} // bulkDiffusivityMeasurements2015
} // investigations

#endif /* fit_a_b1_b2_RC_h */
