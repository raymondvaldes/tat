//
//  offset_measurement.cpp
//  tat
//
//  Created by Raymond Valdes on 8/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "offset_measurement.hpp"
#include <cassert>
#include <cmath>
#include <utility>

#include "units.h"

#include "math/special_functions/bessel_j/J1.h"
using math::special_functions::bessel::J1;

#include "math/numIntegration/integrate.h"
#include "thermal/model/oneLayer2D/infinite_disk/complex/h_surface.h"
#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/point_measurement.h"
#include "math/calculus/mean_value/offset_circle/offset_circle.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace offset_detector{

using std::pair;
using std::complex;
using std::vector;
using math::special_functions::bessel::J1;
using namespace units;
using std::isnormal;
using math::transform::iHankelSettings;
using math::complex::properties;
using math::calculus::mean_value::offset_circle;

auto offset_measurement
(
  units::quantity< units::si::dimensionless > const b1_beamRadius,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::dimensionless > const b2_viewRadius ,
  units::quantity< units::si::dimensionless > const b3_view_offset,
  units::quantity< units::si::temperature > deltaT,
  math::transform::iHankelSettings const & /*settings*/
)
noexcept -> math::complex::properties< units::si::temperature >
{
  assert( l > 0 );
  assert( b3_view_offset > 0 );
  assert( b2_viewRadius > 0 );
  auto const a = quantity< length >::from_value( b3_view_offset );
  auto const b = quantity< length >::from_value( b2_viewRadius );
  
  
  auto const T_phase =
  [ &b1_beamRadius, &l, &deltaT ]
  ( quantity< length > const r_dummy_dimensional ) noexcept -> double
  {
    auto const r_nondimensional = r_dummy_dimensional.value();
    
    auto const complex_temperature =
    point_measurement( b1_beamRadius, l, deltaT, r_nondimensional );
    
    auto const phase = complex_temperature.phase;
    auto const phase_value = phase.value();
    
    return phase_value;
  };

  auto const phase_offset =
  quantity< plane_angle >::from_value( offset_circle( T_phase, a, b ) );

  auto const dummy_amplitude = quantity< si::temperature >::from_value(0.99);
  return properties< si::temperature >( phase_offset , dummy_amplitude ) ;
}

} // namespace offset_detector
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
