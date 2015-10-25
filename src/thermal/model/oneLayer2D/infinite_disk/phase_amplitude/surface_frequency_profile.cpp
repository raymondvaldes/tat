//
//  surface_frequency_profile.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/infinite_disk/phase_amplitude/surface_frequency_profile.h"
#include "thermal/model/oneLayer2D/complex/surface_phase_amplitude.h"
#include "thermal/model/oneLayer2D/dimensionless/thermal_penetration.h"

#include "algorithm/algorithm.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{
namespace temperature{

using namespace units;
using math::complex::properties;
using namespace units;
using std::vector;
using algorithm::transform;

auto surface_frequency_profile(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::temperature > const deltaT,
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha,
  units::quantity< units::si::dimensionless > const radial_position
) noexcept -> std::vector< math::complex::properties< units::si::temperature >>
{
  assert( b > 0) ;
  assert( deltaT > 0 * kelvin ) ;
  assert( !frequencies.empty() );
  assert( L > 0 * meters ) ;
  assert( alpha.value() > 0  ) ;
  assert( radial_position > 0 );
  
  auto results =
  vector< properties< si::temperature > >( frequencies.size()  );
  
  transform( frequencies, results.begin(), [&]( auto const f ) noexcept
  {
    auto const l = dimensionless::thermal_penetration( f, L, alpha ) ;
    auto const p = complex::surface_phase_amplitude( radial_position, b , l , deltaT );

    return p;
  } );

  return results;
}

} // namespace temperature
} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
