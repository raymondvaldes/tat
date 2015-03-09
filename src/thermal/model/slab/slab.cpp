//
//  slab.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include <complex>

#include "thermal/model/slab/slab.h"

namespace thermal {

namespace model {

namespace slab {

auto neumann_and_direchlet_BC(
  units::quantity< units::si::length> x ,
  units::quantity< units::si::heat_flux > I_transient,
  units::quantity< units::si::thermal_conductivity > k,
  units::quantity< units::si::length > characteristic_length,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::frequency > f
)
noexcept -> double
{
  using math::differential::waveEquation::analytical_solution_10;

  assert( x.value() > 0 ) ;
  assert( I_transient.value() > 0 ) ;
  assert( k.value() > 0 ) ;
  assert( characteristic_length.value() > 0 ) ;
  assert( alpha.value() > 0 ) ;
  assert( f.value() > 0 ) ;

  using units::pow;
  using units::sqrt;
  using units::si::radians;
  using std::complex;
  using units::quantity;
  using units::si::dimensionless;
  
  auto const L = characteristic_length;
  auto const Io = I_transient;
  
  auto const w = M_2_PI * f;
  
  auto const A_non = quantity<dimensionless>(1) ;
  auto const w_non = w * pow<2>( L ) / alpha ;
  
  auto const i_imag = complex< double >( 0, 1 ) ;
  auto const i_non = quantity< dimensionless, complex<double> >( i_imag ) ;
  
  auto const Kappa = sqrt( i_non * w_non ) ;
  
  auto const x_non = x / L ;
  auto const L_b = L / L ;

  auto const s_x = analytical_solution_10( x_non, Kappa, A_non, L_b ) ;

  return 0;
}

  
} // namespace slab
  
} // namespace model
  
} // namespace thermal
