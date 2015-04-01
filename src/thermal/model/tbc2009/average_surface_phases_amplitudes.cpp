//
//  average_surface_phases_amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "average_surface_phases_amplitudes.h"
#include "thermal/model/tbc2009/complexT/average_surface_phase_amplitude.h"
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "algorithm/algorithm.h"
#include "thermal/model/tbc2009/dimensionless/thermal_penetration.h"

namespace thermal {
namespace model {
namespace tbc2009{

using complexT::average_surface_phase_amplitude;
using namespace units;
using std::vector;
using std::pair;
using algorithm::transform;

auto
average_surface_phases_amplitudes
(
  units::quantity< units::si::dimensionless > const view_radius,
  std::vector< units::quantity< units::si::frequency > > const frequencies,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_substrate
) noexcept -> std::vector< std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> > >
{
  auto results =
  vector< pair< quantity< plane_angle >,
                quantity< si::dimensionless > > >( frequencies.size()  );
  auto const alpha_coat = pow<2>( tp.a_sub ) * alpha_substrate;

  transform( frequencies, results.begin(), [&]( auto const f ) noexcept
  {
    auto const l = dimensionless::thermal_penetration(f, L, alpha_coat );
    return average_surface_phase_amplitude( view_radius, hp, tp, l );
  } );

  return results;
}


} // namespace tbc2009
} // namespace thermal
} // namespace model
