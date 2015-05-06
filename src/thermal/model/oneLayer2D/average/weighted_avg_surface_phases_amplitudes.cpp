//
//  weighted_avg_surface_phases_amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/average/weighted_avg_surface_phases_amplitudes.h"
#include <cassert>

#include "thermal/model/oneLayer2D/complex/weighted_average/surface_phase_amplitude.h"
#include "thermal/model/oneLayer2D/dimensionless/thermal_penetration.h"
#include "algorithm/algorithm.h"

using math::complex::properties;
using namespace units;
using std::vector;
using algorithm::transform;
using thermal::model::oneLayer2D::complex::weighted_average::surface_phase_amplitude;

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace average{
auto
weighted_avg_surface_phases_amplitudes
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  std::vector< units::quantity< units::si::frequency> > const & frequencies,
  units::quantity< units::si::length> const L,
  units::quantity< units::si::thermal_diffusivity> const alpha,
  units::quantity< units::si::temperature > const steady_state_temperature,
  units::quantity< units::wavelength > const detector_wavelength
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
    auto const p =
      surface_phase_amplitude( b , l , deltaT , view_radius, steady_state_temperature, detector_wavelength );
    return p;
  } );

  return results;
}

} // namespace average
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
