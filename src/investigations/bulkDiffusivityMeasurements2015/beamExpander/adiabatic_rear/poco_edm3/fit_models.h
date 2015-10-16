//
//  fit_models.h
//  tat
//
//  Created by Raymond Valdes on 9/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_models_h_092815
#define fit_models_h_092815

#include "sept28/A1_rear_190degC.h"
#include "sept28/B1_rear_179degC.h"
#include "sept28/A1_rear_100degC.h"

#include "fit_a_b1_b2_RC.h"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace adiabatic_rear{
namespace poco_edm3{

inline auto fit_models( void ) noexcept -> void
{
  using namespace units;
  using std::vector;
  using thermal::experimental::observations::Slab;
  
  auto const specimens = vector< Slab >( {
    sept28::A1_rear_190degC(),
//    sept28::B1_rear_179degC(),
//    sept28::A1_rear_100degC()
  } ) ;
  
  auto const detector_radius = quantity< length >( .25 * millimeters  ) ;
  
  fit_a_b1_b2_RC( specimens, detector_radius );
}

} // namespace poco_edm3
} // namespace adiabatic_rear
} // namespace beamExpander
} // bulkDiffusivityMeasurements2015
} // investigations

#endif /* fit_models_h */
