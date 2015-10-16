//
//  fit_models.hpp
//  tat
//
//  Created by Raymond Valdes on 9/8/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_models_hpp_beamExpander_sept4
#define fit_models_hpp_beamExpander_sept4

#include <vector>

#include "specimenB.hpp"
#include "specimenE.hpp"
#include "specimenF.hpp"
#include "specimenH.hpp"

#include "fit_a_b1_RC.h"
#include "fit_a_b1_b2_RC.h"
#include "fit_a_b2_RC.hpp"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace sept4{

inline auto fit_models( void ) noexcept -> void
{
  using namespace units;
  using std::vector;
  using thermal::experimental::observations::Slab;
  
  auto const specimens = vector< Slab >( {
    specimenB(),
//    specimenE(),
//    specimenF(),
//    specimenH()
  } ) ;
  
  auto const detector_radius = quantity< length >( .25 * millimeters  ) ;
  
  fit_a_b1_b2_RC( specimens, detector_radius );

//  fit_a_b1_RC( specimens );

//  auto const detector_offset = quantity< length >( .25 * millimeters );
//  fit_a_b2_RC( specimens, detector_offset );
}

} // namespace sept4
} // namespace beamExpander
} // namespace bulkDiffusivityMeasurements2015
} // namespace investigations

#endif /* fit_models_hpp */
