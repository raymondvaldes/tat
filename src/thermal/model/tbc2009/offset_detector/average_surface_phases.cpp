//
//  average_surface_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/tbc2009/offset_detector/average_surface_phases.h"
#include "thermal/model/tbc2009/offset_detector/surface_T_phases_amplitudes.h"
#include "algorithm/algorithm.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace offset_detector {

using namespace units;
using std::vector;
using algorithm::transform;

auto
average_surface_phases
(
  std::vector< units::quantity< units::si::frequency > > const frequencies,
  dimensionless::HeatingProperties const & hp,
  dimensionless::ThermalProperties const & tp,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_substrate,
  units::quantity< units::si::dimensionless > const offset,
  units::quantity< units::si::dimensionless > const view_radius
) noexcept -> std::vector< units::quantity< units::si::plane_angle >  >
{
  auto const phase_amplitude_pairs = surface_T_phases_amplitudes(
  frequencies, hp, tp, L, alpha_substrate, offset, view_radius );
 
  auto phases = vector< quantity< plane_angle > >( frequencies.size() );
  
  transform( phase_amplitude_pairs, phases.begin(), []
  ( auto const phase_amplitude_pair ) noexcept
  {
    auto const phase = phase_amplitude_pair.first;
    return phase;
  } ) ;
  
  return phases;
}

} // namespace offset_detector
} // namespace tbc2009
} // namespace model
} // namespace thermal
