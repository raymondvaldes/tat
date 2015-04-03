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

namespace thermal {
namespace model {
namespace tbc2009 {
namespace offset_detector {

using complexT::offset_detector::average_surface_phase_amplitude;
using namespace units;
using std::vector;
using std::pair;
using algorithm::transform;

auto
surface_T_phases_amplitudes
(
  std::vector< units::quantity< units::si::frequency > > const frequencies,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_substrate,
  units::quantity< units::si::dimensionless > const offset,
  units::quantity< units::si::dimensionless > const view_radius
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
    return average_surface_phase_amplitude( hp, tp, l, offset, view_radius );
  } );

  return results;



}

} // namespace offset_detector
} // namespace tbc2009
} // namespace model
} // namespace thermal
