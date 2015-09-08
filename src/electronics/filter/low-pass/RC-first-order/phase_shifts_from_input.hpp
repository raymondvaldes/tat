//
//  phase_shifts_from_input.hpp
//  tat
//
//  Created by Raymond Valdes on 9/1/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef phase_shifts_from_input_cpp
#define phase_shifts_from_input_cpp

#include "units.h"
#include <vector>

namespace electronics{
namespace filter{
namespace low_pass{
namespace RC_first_order{

auto phase_shifts_from_input(
  std::vector< units::quantity< units::si::frequency > > const & ac_frequencies,
  units::quantity< units::si::electrical_time_constant > const tau
) noexcept -> std::vector< units::quantity< units::si::plane_angle > > ;

} // namaepsace electronics
} // namespace filter
} // namespace low_pass
} // namespace RC_first_order

#endif /* phase_shifts_from_input_cpp */
