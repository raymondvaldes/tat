//
//  fast_measurement.cpp
//  tat
//
//  Created by Raymond Valdes on 5/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//


#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/centered_with_view/fast_measurement.h"
#include <cassert>
#include <cmath>

#include "units.h"

#include "math/special_functions/bessel_j/J1.h"
using math::special_functions::bessel::J1;

#include "math/numIntegration/integrate.h"
#include "thermal/model/oneLayer2D/infinite_disk/complex/h_surface.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace centered_with_view{

using std::complex;
using std::vector;
using math::special_functions::bessel::J1;
using namespace units;
using std::isnormal;
using math::transform::iHankelSettings;
using math::complex::properties;

auto fast_measurement
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::dimensionless > const r_e ,
  math::transform::iHankelSettings const & settings
)
noexcept -> math::complex::properties< units::si::temperature >
{
  auto const h = [ b, l ]( auto const nu_ ) noexcept {
        return oneLayer2D::complex::h_surface( nu_, l, b );
  };
  
  // given integrate f(x) from a to b.  Must satisfy F(a) = 0;
  auto const func = [ & ]
  ( vector< double > const & /*y*/, vector< double > & dy, double const nu )
  noexcept -> void
  {
    auto const hFunc = h( nu ).value() * J1( nu * r_e ).value();
    dy[0] = hFunc.real();
    dy[1] = hFunc.imag();
  };

  auto result = vector< double >( {0,0} );


  auto const x0 = double(0) ;
  auto const x1 = settings.nu_end.value() ;
  auto const dx_intial_step = double( 0.01 );
  math::numIntegration::integrate( func, result, x0, x1, dx_intial_step );

  auto const area = complex<double>( result[0], result[1] );

  assert( isfinite( area.real() ) );
  assert( isfinite( area.imag() ) );
  
  auto const phase = quantity< plane_angle >( -arg( area ) * radians);
  auto const amplitude = quantity< si::temperature >( abs( area ) * kelvin );

  return properties< si::temperature >( phase , amplitude ) ;
}
}
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
