//
//  asdf.h
//  tat
//
//  Created by Raymond Valdes on 9/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_models_asdf_h
#define fit_models_asdf_h

#include "run1_rear_70degC.h"
#include "fit_a_b1_b2_RC.h"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace adiabatic_rear{
namespace aluminum_target{
namespace sept24{

inline auto fit_models( void ) noexcept -> void
{
  using namespace units;
  using std::vector;
  using thermal::experimental::observations::Slab;
  
  auto const specimens = vector< Slab >( {
    run1_rear_70degC(),
  } ) ;
  
  auto const detector_radius = quantity< length >( .25 * millimeters  ) ;
  
  fit_a_b1_b2_RC( specimens, detector_radius );
}

} // namespace sept24
} // namespace aluminum_target
} // namesapce adiabatic_rear
} // namespace beamExpander
} // namespace bulkDiffusivityMeasurements2015
} // namespace investigations

#endif /* asdf_h */
