//
//  phase_shifts_from_input.cpp
//  tat
//
//  Created by Raymond Valdes on 9/1/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "phase_shifts_from_input.hpp"
#include "phase_shift_from_input.hpp"

#include "algorithm/algorithm.h"

namespace electronics{
namespace filter{
namespace low_pass{
namespace RC_first_order{

using algorithm::for_each;
using algorithm::transform;
using std::vector;
using namespace units;
using std::begin;

auto phase_shifts_from_input(
  std::vector< units::quantity< units::si::frequency > > const & ac_frequencies,
  units::quantity< units::si::electrical_time_constant > const tau
) noexcept -> std::vector< units::quantity< units::si::plane_angle > >
{
  // establish preconditions
  assert( ac_frequencies.size() > 0 );
  assert( tau.value() > 0 ) ;
  for_each( ac_frequencies, []( auto& each_frequency ){
    assert( each_frequency.value() > 0 );
  });

  //
  auto const size = ac_frequencies.size();
  auto phase_shifts = vector< quantity< si::plane_angle > >( size );
  
  transform( ac_frequencies, begin( phase_shifts ) ,
    [ tau ]( auto const ac_frequncy ) noexcept
    {
      return phase_shift_from_input( ac_frequncy, tau );
    });
  
  return phase_shifts;
}

} // namaepsace electronics
} // namespace filter
} // namespace low_pass
} // namespace RC_first_order
