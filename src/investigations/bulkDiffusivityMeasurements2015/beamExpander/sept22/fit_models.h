//
//  fit_models.h
//  tat
//
//  Created by Raymond Valdes on 9/22/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_models_h_092215
#define fit_models_h_092215

#include <vector>

#include "specimenE.h"
#include "fit_a_b1_b2_RC.h"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace sept22{

inline auto fit_models( void ) noexcept -> void
{
  using namespace units;
  using std::vector;
  using thermal::experimental::observations::Slab;
  
  auto const specimens = vector< Slab >( {
//    specimenB(),
    specimenE(),
//    specimenF(),
//    specimenH()
  } ) ;
  
  auto const detector_radius = quantity< length >( .25 * millimeters  ) ;
  
  fit_a_b1_b2_RC( specimens, detector_radius );

//  fit_a_b1_RC( specimens );

//  auto const detector_offset = quantity< length >( .25 * millimeters );
//  fit_a_b2_RC( specimens, detector_offset );
}

} // namespace sept22
} // namespace beamExpander
} // namespace bulkDiffusivityMeasurements2015
} // namespace investigations

#endif /* fit_models_h */
