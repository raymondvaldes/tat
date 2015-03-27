//
//  surface_temperature.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_twoLayer_complex_surface_temperature__
#define __tat_thermal_model_twoLayer_complex_surface_temperature__

#include "units.h"
#include "thermal/model/slab/slab.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

auto surface_temperature
(
  units::quantity< units::si::frequency > const f,
  slab::Slab const & first_layer,
  slab::Slab const & second_layer,
  units::quantity< units::si::dimensionless > const R_non 
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >;

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal

#endif /* defined(__tat_thermal_model_twoLayer_complex_surface_temperature__) */
