//
//  tempeature_nd.cpp
//  tat
//
//  Created by Raymond Valdes on 5/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/reverseIntegration/tempeature_nd.h"
#include <cassert>
#include <iostream>

#include "algorithm/algorithm.h"
#include "math/special_functions/bessel.h"
#include "math/numIntegration/integrate.h"
#include "units.h"
#include "thermal/model/oneLayer2D/complex/h_surface.h"
#include <cmath>

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{
namespace reverseIntegration{

using std::complex;
using std::vector;
using math::special_functions::bessel_j;
using namespace units;
using std::isnormal;
using math::transform::iHankelSettings;

auto temperature_nd
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::dimensionless > const r_e,
  math::transform::iHankelSettings const & settings
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  auto const z = quantity<si::dimensionless>::from_value( 0. );
  auto const x0 = double(0) ;
  auto const x1 = settings.nu_end.value() ;
  auto const dx_intial_step = double( 0.01 );
  
  auto const J1 = []( auto const & x ) noexcept { return bessel_j( 1, x ); };
  
  auto const h = [ b, l, z ]( auto const nu_ , auto const z_ ) noexcept {
        return h_surface( nu_, l, b );
    };
  
  std::cout << "\n";
  std::cout << "nu" <<"\t"<< "h( nu, z=0 )" <<"\t"<< "J1( nu * r_e )" << "\n";

  auto const fast_hankel_function = [&]( double const & nu ) noexcept
  {
    auto const h_out =  h( nu, z ).value() * J1( nu * r_e ).value() ;

std::cout << nu <<"\t"<< h( nu, z ).value() <<"\t"<< J1( nu * r_e ).value() << "\n";

    return h_out;
  };

  // given integrate f(x) from a to b.  Must satisfy F(a) = 0;
  auto const func = [ &h, &z,&fast_hankel_function ]
  ( vector< double > const & y, vector< double > & dy, double const nu )
  noexcept -> void
  {
    auto const hFunc = fast_hankel_function( nu );
    dy[0] = hFunc.real();
    dy[1] = hFunc.imag();
  };

  auto result = vector< double >( {0,0} );

  math::numIntegration::integrate( func, result, x0, x1, dx_intial_step );

  auto const area = complex<double>( result[0], result[1] );
  auto const area_quantity = quantity< dimensionless, complex<double> >( area );

  assert( isfinite( area_quantity.value().real() ) );
  assert( isfinite( area_quantity.value().imag() ) );
  
  return area_quantity;
}

}}}}}
