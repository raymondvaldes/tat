//
//  average_surface_phase_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 4/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/offset_detector/average_surface_phase_amplitude.h"
#include "math/calculus/mean_value/offset_circle/offset_circle.h"
#include "thermal/model/oneLayer2D/complex/surface_phase_amplitude.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace offset_detector{

using namespace units;
using std::make_pair;
using namespace math::calculus;
using math::complex::properties;

auto avg_surface_phase_amplitude
(
  units::quantity< units::si::dimensionless > const b_laser,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  units::quantity< units::si::dimensionless> const detector_offset
) noexcept -> math::complex::properties< units::si::temperature >
{
  assert( b_laser > 0 ) ;
  assert( l > 0 );
  assert( deltaT > 0 * kelvin) ;
  assert( view_radius > 0 );
  assert( detector_offset > 0 );

  auto const a = quantity<length>::from_value( detector_offset );
  auto const b = quantity<length>::from_value( view_radius );
  
  auto const f_r =
  [ &b_laser, &l, &deltaT ]( quantity< length > const r ) noexcept
  {
    auto const r_dim = quantity< si::dimensionless >( r.value() );
    auto const p = complex::surface_phase_amplitude( r_dim, b_laser, l, deltaT );
    return make_pair( p.phase.value(), p.amplitude.value() ) ;
  };
  
  auto const mean = mean_value::offset_circle( f_r, a, b ) ;
  
  auto const mean_phase = quantity< plane_angle >::from_value( mean.first );
  auto const mean_amplitude = quantity< si::temperature >::from_value( mean.second );
  return properties< si::temperature >( mean_phase, mean_amplitude );
}

} // namespace offset_detector
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
