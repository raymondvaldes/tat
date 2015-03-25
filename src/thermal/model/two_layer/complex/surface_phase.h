//
//  surface_phase.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_twoLayer_complex_surface_phase__
#define __tat_thermal_model_twoLayer_complex_surface_phase__

#include "units.h"
#include "thermal/model/slab/slab.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

auto surface_phase
(
  units::quantity< units::si::frequency > const f,
  slab::Slab const & first_layer,
  slab::Slab const & second_layer
)
noexcept -> units::quantity< units::si::plane_angle >;

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal

#endif /* defined(__tat_thermal_model_twoLayer_complex_surface_phase__) */
