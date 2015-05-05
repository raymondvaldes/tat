//
//  surface_phase_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/weighted_average/surface_phase_amplitude.h"
#include "thermal/model/oneLayer2D/complex/surface_phase_amplitude.h"
#include "math/calculus/mean_value/circle/circle_complex.h"
#include "thermal/equipment/detector/spot_view/spot_view.h"

using math::calculus::mean_value::circle_complex;
using math::complex::properties;
using thermal::equipment::detector::spot_view_2;
using std::make_pair;
using namespace units;

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{
namespace weighted_average{

auto surface_phase_amplitude
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  units::quantity< units::si::temperature> const T_steady_state,
  units::quantity< units::si::wavelength> const detector_wavelength
) noexcept -> math::complex::properties< units::si::temperature >
{
  auto const f_r =
  [ &b, &l, &deltaT ]
  ( double const r ) noexcept -> std::pair< double, double >
  {
    auto const r_dim = quantity<si::dimensionless>( r );
    auto const p = complex::surface_phase_amplitude( r_dim, b, l, deltaT );
    return make_pair( p.phase.value(), p.amplitude.value() ) ;
  };

  auto const view_radius_d = double( view_radius.value() );
  auto const dr = double( 0.001 );
  auto const mean = circle_complex( f_r, view_radius_d, dr );
  
  auto const mean_phase = quantity< plane_angle >::from_value( mean.first );
  auto const mean_amplitude = quantity< si::temperature >::from_value( mean.second );
  return properties< si::temperature >( mean_phase, mean_amplitude );
}

} // namespace weighted_average
} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
