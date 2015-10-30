//
//  fitted_measurements.cpp
//  tat
//
//  Created by Raymond Valdes on 3/22/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "fitted_measurements.h"

#include "math/curveFit/get_initial_conditions.h"
#include "physics/classical_mechanics/kinematics.h"

using namespace units;
using math::curveFit::cosine;
using math::curveFit::get_initial_conditions;
using physics::classical_mechanics::frequency_to_angularFrequency;

namespace thermal {
  
namespace equipment {

namespace detector {

auto fitted_measurements
(
  Measurements const & m,
  units::quantity< units::si::frequency > const f
)
noexcept -> math::functions::Cosine< units::si::electric_potential >
{
  auto const omega = frequency_to_angularFrequency( f );

  return fitted_measurements( m, omega );
}

auto fitted_measurements
(
  Measurements const & m,
  units::quantity< units::si::angular_frequency > const omega
)
noexcept -> math::functions::Cosine< units::si::electric_potential >
{
  auto const times = m.referenceTimes();
  auto const signals = m.signals_electical_potential();
  auto const data = make_pair( times, signals );

  auto const initial = get_initial_conditions( data, omega );
  
  auto const cosine_phase = quantity< plane_angle >( 0 * radians) ;
  auto const fit_cosine = cosine( data, initial, cosine_phase );

  return fit_cosine.fitted_cosine;
}

} // namespace detector
  
} // namespace equipment
  
} // namespace thermal
