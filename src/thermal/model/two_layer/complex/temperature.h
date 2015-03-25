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
#include "thermal/model/slab/slab.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

auto temperature
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::frequency > const f,
  slab::Slab const & first_layer,
  slab::Slab const & second_layer
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >;

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal

#endif /* defined(__tat__nondimensional__) */
