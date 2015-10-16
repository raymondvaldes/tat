//
//  frequency_sweep.h
//  tat
//
//  Created by Raymond Valdes on 5/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_08307_frequency_sweep__
#define __tat_08307_frequency_sweep__

#include <vector>

#include "units.h"
#include "math/complex/properties.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/model/complex/temperatures.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {

auto
frequency_sweep
(
  units::quantity< units::si::dimensionless > const b ,
  units::quantity< units::si::temperature > const deltaT ,
  units::quantity< units::si::dimensionless > const r_e ,
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> std::vector< math::complex::properties< units::si::temperature > > ;


auto
frequency_sweep
(
  slab::Slab const & slab,
  Optics const & optics,
  equipment::laser::Modulation_frequencies const & frequencies
)
noexcept -> thermal::model::complex::Temperatures ;


} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__frequency_sweep__) */
