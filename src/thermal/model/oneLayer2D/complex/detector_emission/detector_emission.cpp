//
//  detector_emission.cpp
//  tat
//
//  Created by Raymond Valdes on 5/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/detector_emission/detector_emission.h"
#include "thermal/model/oneLayer2D/complex/surface_phase_amplitude.h"
#include "math/numIntegration/integrate.h"

#include <vector>

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using std::vector;
using namespace units;
using math::complex::properties;

auto detector_emission
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  units::quantity< units::si::temperature> const T_steady_state,
  units::quantity< units::si::wavelength> const detector_wavelength
) noexcept -> std::complex< double >
{
  using math::numIntegration::integrate;
  using std::pow;
  using std::vector;
  using std::make_pair;
  
  // find the mean value of a function from a to b.
  // mean_value = 2/(R^2) * Int[ ( f * r ) dr, 0, R ]

  auto const func = [&]
  (
    vector< double > const & y,
    vector< double > & dr,
    double const r
  ) noexcept -> void
  {
    auto const r_dim = quantity<si::dimensionless>( r );
    auto const p = complex::surface_phase_amplitude( r_dim, b, l, deltaT );
    auto const p_cmplx = p.complex_value();
    
    dr[0] = p_cmplx.real() * r;
    dr[1] = p_cmplx.imag() * r;
  };

  auto f_0= vector< double > ( { 0, 0 } );
  auto const r0 = double(0) ;
  auto const r1 = view_radius.value() ;
  auto const dr_i_step = ( r1 - r0 ) / 100. ;
  
  integrate( func, f_0, r0 , r1, dr_i_step );

  
  auto const detector_real =  f_0[0] ;
  auto const detector_imag =  f_0[1] ;

  return std::complex<double>( detector_real, detector_imag );

//  auto const mean_pair =
//  properties< si::temperature >( mean_phase, mean_amplitude ) ;
}


} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
