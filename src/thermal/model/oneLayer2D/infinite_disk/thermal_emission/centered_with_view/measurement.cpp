//
//  measurement.cpp
//  tat
//
//  Created by Raymond Valdes on 5/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/centered_with_view/measurement.h"

#include <cmath>
#include <utility>
#include <vector>
#include "math/numIntegration/integrate.h"
#include "thermal/model/oneLayer2D/infinite_disk/complex/surface_phase_amplitude.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace centered_with_view {

using std::pow;
using std::make_pair;
using std::vector;
using std::complex;
using std::abs;
using std::arg;
using namespace units;
using math::complex::properties;
using math::numIntegration::integrate;

auto measurement
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  units::quantity< units::si::temperature> const /*T_steady_state*/,
  units::quantity< units::si::wavelength> const /*detector_wavelength*/
)
noexcept -> math::complex::properties< units::si::temperature >
{
  auto const func = [&]
  (
    vector< double > const & /*y*/,
    vector< double > & dr,
    double const r
  ) noexcept -> void
  {
    auto const dT = deltaT;
    auto const r_d = quantity<si::dimensionless>( r );
    auto const T = oneLayer2D::complex::surface_phase_amplitude( r_d, b, l, dT);
    auto const T_i = T.complex_value();
    
    dr[0] = T_i.real() * r;
    dr[1] = T_i.imag() * r;
  };

  auto f_0= vector< double > ( { 0, 0 } );
  auto const r0 = double(0) ;
  auto const r1 = view_radius.value() ;
  auto const dr_i_step = ( r1 - r0 ) / 100. ;
  
  integrate( func, f_0, r0 , r1, dr_i_step );

  auto const signal_value = complex< double >( f_0[0], f_0[1] );
  auto const phase = quantity< plane_angle >( arg( signal_value ) * radians);
  auto const amplitude = quantity< si::temperature >( abs( signal_value ) * kelvin );

  return properties< si::temperature >( phase , amplitude );
}

}
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
