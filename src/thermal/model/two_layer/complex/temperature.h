//
//  nondimensional.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_twolayer_nondimensional__
#define __tat_thermal_model_twolayer_nondimensional__

#include "units.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

auto temperature
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::frequency > const f,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_1,
  units::quantity< units::si::thermal_diffusivity > const alpha_2,
  units::quantity< units::si::thermal_conductivity > const k_1,
  units::quantity< units::si::thermal_conductivity > const k_2
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >;

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal

#endif /* defined(__tat__nondimensional__) */
