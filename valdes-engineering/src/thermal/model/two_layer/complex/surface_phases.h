//
//  surface_phases.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_twoLayer_complex_surface_phases__
#define __tat_thermal_model_twoLayer_complex_surface_phases__

#include <vector>
#include "units.h"
#include "thermal/model/slab/slab.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

auto surface_phases
(
  std::vector< units::quantity< units::si::frequency > > const & freqs,
  slab::Slab const & first_layer,
  slab::Slab const & second_layer,
  units::quantity< units::si::dimensionless > const R_non
)
noexcept -> std::vector< units::quantity< units::si::plane_angle > >;

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal

#endif /* defined(__tat_thermal_model_twoLayer_complex_surface_phases__) */
