//
//  fit_models.h
//  tat
//
//  Created by Raymond Valdes on 9/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_models_h_09231513245
#define fit_models_h_09231513245

#include <vector>

#include "specimenE.h"
#include "specimenE_low_laser.h"
#include "fit_a_b1_b2_RC.h"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace heated_stage{
namespace sept23{

inline auto fit_models( void ) noexcept -> void
{
  using namespace units;
  using std::vector;
  using thermal::experimental::observations::Slab;
  
  auto const specimens = vector< Slab >( {
//    specimenE(),
    specimenE_low_laser()
  } ) ;
  
  auto const detector_radius = quantity< length >( .25 * millimeters  ) ;
  
  fit_a_b1_b2_RC( specimens, detector_radius );

//  fit_a_b1_RC( specimens );
//  auto const detector_offset = quantity< length >( .25 * millimeters );
//  fit_a_b2_RC( specimens, detector_offset );
}

} // namespace sept23
} // namespace heated_stage
} // namespace beamExpander
} // namespace bulkDiffusivityMeasurements2015
} // namespace investigations

#endif /* fit_models_h */
