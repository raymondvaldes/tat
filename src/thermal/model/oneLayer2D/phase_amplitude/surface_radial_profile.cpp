//
//  surface_radial_profile.cpp
//  tat
//
//  Created by Raymond Valdes on 5/1/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/phase_amplitude/surface_radial_profile.h"
#include "thermal/model/oneLayer2D/complex/surface_phase_amplitude.h"
#include "thermal/model/oneLayer2D/dimensionless/thermal_penetration.h"

#include "algorithm/algorithm.h"

using namespace units;
using math::complex::properties;
using namespace units;
using std::vector;
using algorithm::transform;

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace phase_amplitude{

auto surface_radial_profile(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::temperature > const deltaT,
  std::vector< units::quantity< units::si::dimensionless > > const & radial_positions,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha,
  units::quantity< units::si::frequency > const f
) noexcept -> std::vector< math::complex::properties< units::si::temperature >>
{
  assert( b > 0) ;
  assert( deltaT > 0 * kelvin ) ;
  assert( !radial_positions.empty() );
  assert( L > 0 * meters ) ;
  assert( alpha.value() > 0  ) ;

  auto results =
  vector< properties< units::si::temperature > >( radial_positions.size()  );
  
  transform( radial_positions, results.begin(), [&]( auto const r ) noexcept
  {
    auto const l = dimensionless::thermal_penetration( f, L, alpha ) ;
    auto const p = complex::surface_phase_amplitude( r, b , l , deltaT );

    return p;
  } );

  return results;

}

} // namespace phase_amplitude
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
