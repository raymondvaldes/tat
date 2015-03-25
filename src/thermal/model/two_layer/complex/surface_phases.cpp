//
//  surface_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/two_layer/complex/surface_phases.h"
#include "thermal/model/two_layer/complex/surface_phase.h"
#include "physics/classical_mechanics/kinematics.h"
#include "algorithm/algorithm.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

using namespace units;
using std::vector;
using algorithm::transform;

auto surface_phases
(
  std::vector< units::quantity< units::si::frequency > > const & freqs,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_1,
  units::quantity< units::si::thermal_diffusivity > const alpha_2,
  units::quantity< units::si::thermal_conductivity > const k_1,
  units::quantity< units::si::thermal_conductivity > const k_2
)
noexcept -> std::vector< units::quantity< units::si::plane_angle > >
{
  auto phases = vector< quantity< plane_angle > >( freqs.size() );
  
  transform( freqs, phases.begin(), [&]( auto const & f ) noexcept
  {
    auto const phase = surface_phase( f, L, alpha_1, alpha_2, k_1, k_2 );
    return phase;
  } );
  return phases;
}

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal
