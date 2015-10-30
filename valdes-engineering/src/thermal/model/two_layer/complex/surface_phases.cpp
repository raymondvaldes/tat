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
  slab::Slab const & first_layer,
  slab::Slab const & second_layer,
  units::quantity< units::si::dimensionless > const R_non
)
noexcept -> std::vector< units::quantity< units::si::plane_angle > >
{
  auto phases = vector< quantity< plane_angle > >( freqs.size() );
  
  transform( freqs, phases.begin(), [&]( auto const & f ) noexcept
  {
    auto const phase = surface_phase( f, first_layer, second_layer, R_non ) ;
    return phase;
  } );
  return phases;
}

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal
