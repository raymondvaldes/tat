//
//  inverseHankel.cpp
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "inverseHankel.h"
#include "algorithm/algorithm.h"
#include "math/special_functions/bessel.h"
#include "math/numIntegration/integrate.h"
#include "units.h"

namespace math {

namespace transform {

using std::complex;
using std::vector;
using math::special_functions::bessel_j;
using namespace units;

iHankelSettings::iHankelSettings
(
  units::quantity< units::si::dimensionless > const nu_end_ ) noexcept
: nu_end( nu_end_ )
{};

auto
inverseHankel
(
  std::function<
  units::quantity< units::si::dimensionless, std::complex<double> >
  ( units::quantity< units::si::dimensionless, double > const,
    units::quantity< units::si::dimensionless, double > const)> const & h,
  units::quantity< units::si::dimensionless, double > const z,
  units::quantity< units::si::dimensionless, double > const r,
  iHankelSettings const & settings 
)
noexcept -> units::quantity< units::si::dimensionless, std::complex<double>>
{
  assert( r.value() >= 0 );
  assert( z.value() >= 0 );
//The inverse hankel involves doing an integration over nu space
// basically i can first evaluate the complex values over the integration
// space and then i can split those into the real and imag values.
// integrate through each one individually.

  /*
  The definite integral of a complex integrand is the sum if the
  intregral of real and complex parts.

  Int[f(x),a,b] = Int[u(x)+i*v[x],a,b] = Int[u(x),a,b] + i * Int[v[x],a,b]
  */
  
  // integration domain
  auto const x0 = double(0) ;
  auto const x1 = settings.nu_end.value() ;
  auto const dx_intial_step = double( 0.1 );
  auto const f_x0 = vector< double > ( { 0 } );
  
  auto const J0 = []( auto const & x ) noexcept { return bessel_j(0, x );};
  
  auto const hankel_function = [&]( double const & nu ) noexcept {
    
    auto const h_out = h( nu, z ).value() * J0( nu * r ).value() * nu;
    return h_out;
  };

  // given integrate f(x) from a to b.  Must satisfy F(a) = 0;
  auto const func_real = [ &h, &z, &r, &hankel_function ]
  (
    vector< double > const & y,
    vector< double > & dy,  // thing integrate
    double const nu
  ) noexcept -> void
  {
    auto const eval = hankel_function( nu ) ;
    dy[0] = eval.real(); ;
  };

  auto const area_real =
  math::numIntegration::integrate( func_real, f_x0, x0, x1, dx_intial_step );
  
  
  auto const func_imag = [ &h, &z, &r, &hankel_function ]
  (
    vector< double > const & y,
    vector< double > & dy,
    double const nu
  ) noexcept -> void
  {
    auto const eval = hankel_function( nu ) ;
    dy[0] = eval.imag(); ;
  };
  
  auto const area_imag =
  math::numIntegration::integrate( func_imag, f_x0, x0, x1, dx_intial_step );
  

  auto const area = complex<double>( area_real, area_imag );
  auto const area_quantity = quantity< dimensionless, complex<double> >( area );

  return area_quantity;
}

} // namespace transform
  
} // namespace math
