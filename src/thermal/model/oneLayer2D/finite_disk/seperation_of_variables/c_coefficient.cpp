//
//  c_coefficient.cpp
//  tat
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include <complex>
#include <cassert>
#include "thermal/model/oneLayer2D/finite_disk/seperation_of_variables/c_coefficient.h"
#include "math/special_functions/bessel_j/J0.h"
#include "math/special_functions/bessel_j/J1.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace seperation_of_variables{

using std::complex;
using namespace units;
using math::special_functions::bessel::J1;
using math::special_functions::bessel::J0;

auto c_coefficient
(
  Lambda const lambda,
  Complex_lambda const complex_lambda,
  disk::Biot const Bi,
  disk::dimensionless::Thickness_w const w,
  disk::dimensionless::Radius_s const s,
  laser_beam::Modulation_depth const m
) noexcept -> C_coefficient
{
  assert( w > 0);
  assert( s > 0 );
  assert( m > 0 && m <= 1);
  assert( Bi >= 0 );

  auto const lam_tilde = complex_lambda;
  auto const c1 =
    quantity<si::dimensionless, complex<double>>( {1, 0} )
      /
    ( lam_tilde * sinh( lam_tilde * w  ) +  Bi * cosh( lam_tilde * w ) );

  auto const c2 = m / ( 2. - m );

  auto const c3 =
    exp( -pow<2>( lambda ) / 4. )
    /
    ( M_PI * pow<2>(s) *  (  pow<2>( lambda * s ) + pow<2>( lambda * s ) ) );

  auto const c = c1 * c2 * c3 ;
  
  return c;
}

} // seperation_of_variables
} // finite_disk
} // oneLayer2d
} // model
} // thermal
