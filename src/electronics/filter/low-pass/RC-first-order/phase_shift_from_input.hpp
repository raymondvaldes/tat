//
//  phase_shift_from_input.hpp
//  tat
//
//  Created by Raymond Valdes on 9/1/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef phase_shift_from_input_cpp
#define phase_shift_from_input_cpp

#include "units.h"


namespace electronics{
namespace filter{
namespace low_pass{
namespace RC_first_order{

auto phase_shift_from_input(
  units::quantity< units::si::frequency > const ac_frequency,
  units::quantity< units::si::electrical_time_constant > const tau
) noexcept -> units::quantity< units::si::plane_angle >;

} // namaepsace electronics
} // namespace filter
} // namespace low_pass
} // namespace RC_first_order

#endif /* phase_shift_from_input_cpp */
