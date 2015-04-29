//
//  avg_surface_phases_amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>

#include "thermal/model/oneLayer2D/avg_surface_phases_amplitudes.h"
#include "thermal/model/oneLayer2D/complex/avg_surface_phase_amplitude.h"
#include "thermal/model/oneLayer2D/dimensionless/thermal_penetration.h"
#include "algorithm/algorithm.h"

namespace thermal {
namespace model {
namespace oneLayer2D {

using math::complex::properties;
using namespace units;
using std::vector;
using algorithm::transform;
using complex::avg_surface_phase_amplitude;

auto
avg_surface_phases_amplitudes
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  std::vector< units::quantity< units::si::frequency> > const & frequencies,
  units::quantity< units::si::length> const L,
  units::quantity< units::si::thermal_diffusivity> const alpha
) noexcept -> std::vector< math::complex::properties< units::si::temperature >>
{
  assert( b > 0) ;
  assert( deltaT > 0 * kelvin ) ;
  assert( view_radius > 0 ) ;
  assert( !frequencies.empty() );

  auto results =
  vector< properties< units::si::temperature > >( frequencies.size()  );

  transform( frequencies, results.begin(), [&]( auto const f ) noexcept
  {
    auto const l = dimensionless::thermal_penetration( f, L, alpha ) ;
    return avg_surface_phase_amplitude( b , l , deltaT , view_radius );
  } );

  return results;
}

} // namespace oneLayer2D
} // namespace model
} // namespace thermal
