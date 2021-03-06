//
//  surface_T_phases_amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "surface_T_phases_amplitudes.h"
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "algorithm/algorithm.h"
#include "thermal/model/tbc2009/dimensionless/thermal_penetration.h"
#include "thermal/model/tbc2009/complexT/offset_detector/average_surface_phase_amplitude.h"
#include "thermal/model/tbc2009/average_surface_phases_amplitudes.h"
#include "thermal/model/tbc2009/dimensionless/coating_diffusivity_from_a.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace offset_detector {

using dimensionless::coating_diffusivity_from_a;
using complexT::offset_detector::average_surface_phase_amplitude;
using namespace units;
using std::vector;
using std::pair;
using algorithm::transform;

auto
surface_T_phases_amplitudes
(
  std::vector< units::quantity< units::si::frequency > > const frequencies,
  dimensionless::HeatingProperties const & hp,
  dimensionless::ThermalProperties const & tp,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_sub,
  units::quantity< units::si::dimensionless > const offset,
  units::quantity< units::si::dimensionless > const view_radius
) noexcept -> std::vector< std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> > >
{
  assert( offset > 0 );
  assert( view_radius > 0 );
  assert( L > 0 * meters );
  assert( !frequencies.empty() );

  auto results =
  vector< pair< quantity< plane_angle >,
                quantity< si::dimensionless > > >( frequencies.size()  );
  
  auto const alpha_coat = coating_diffusivity_from_a( tp.a_sub , alpha_sub );

  transform( frequencies, results.begin(), [&]( auto const f ) noexcept
  {
    auto const l = dimensionless::thermal_penetration(f, L, alpha_coat );
    return average_surface_phase_amplitude( hp, tp, l, offset, view_radius );
  } );

  return results;
}

} // namespace offset_detector
} // namespace tbc2009
} // namespace model
} // namespace thermal
