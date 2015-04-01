//
//  average_surface_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 4/1/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "average_surface_phases_amplitudes.h"
#include "average_surface_phases.h"
#include "algorithm/algorithm.h"

namespace thermal {
namespace model {
namespace tbc2009{

using namespace units;
using std::vector;
using algorithm::transform;

auto
average_surface_phases
(
  units::quantity< units::si::dimensionless > const view_radius,
  std::vector< units::quantity< units::si::frequency > > const frequencies,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_substrate 
) noexcept -> std::vector< units::quantity< units::si::plane_angle >  >
{
  auto const phase_amplitude_pairs = average_surface_phases_amplitudes(
    view_radius, frequencies, hp, tp, L, alpha_substrate );
 
  auto phases = vector< quantity< plane_angle > >( frequencies.size() );
  
  transform( phase_amplitude_pairs, phases.begin(), []
  ( auto const phase_amplitude_pair ) noexcept
  {
    auto const phase = phase_amplitude_pair.first;
    return phase;
  });
  
  return phases;
}

} // namespace tbc2009
} // namespace thermal
} // namespace model
