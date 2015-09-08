//
//  phase_shift_from_input.cpp
//  tat
//
//  Created by Raymond Valdes on 9/1/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "phase_shift_from_input.hpp"
#include <cassert>

#include "physics/classical_mechanics/kinematics.h"


namespace electronics{
namespace filter{
namespace low_pass{
namespace RC_first_order{

using namespace units;
using physics::classical_mechanics::frequency_to_angularFrequency;

auto phase_shift_from_input(
  units::quantity< units::si::frequency > const ac_frequency,
  units::quantity< units::si::electrical_time_constant > const tau
 ) noexcept -> units::quantity< units::si::plane_angle >
{
  assert( ac_frequency.value() > 0 );
  assert( tau > 0 * si::seconds );
  
  auto const ac_angular_frequency = frequency_to_angularFrequency( ac_frequency );
  auto const omega = ac_angular_frequency;
  
  auto const phase_shift =
  quantity< plane_angle>(-atan( omega * tau  / radians )  );

  return phase_shift;
}


} // namaepsace electronics
} // namespace filter
} // namespace low_pass
} // namespace RC_first_order
