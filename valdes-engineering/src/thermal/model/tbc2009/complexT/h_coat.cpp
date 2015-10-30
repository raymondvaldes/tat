//
//  h_coat.cpp
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "h_coat.h"
#include "thermal/model/tbc2009/complexT/nu/hat.h"
#include "thermal/model/tbc2009/complexT/nu/tilde.h"
#include "thermal/model/tbc2009/complexT/F_tilde.h"
#include "thermal/model/tbc2009/complexT/H_tilde.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{

using namespace units;
using std::complex;

auto h_coat
(
  units::quantity< units::si::dimensionless > const nu,
  units::quantity< units::si::dimensionless > const z,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::dimensionless > const l
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  auto const cmplx = []( auto const x, auto const y ){
    return quantity< si::dimensionless, complex<double> >
    ( complex<double>( x, y ) ); };

  auto const Lambda = hp.Lambda;
  auto const R0 = hp.R0;
  auto const R1 = hp.R1;
  auto const b = hp.b;
  auto const gamma = tp.gamma;
  auto const a_sub = tp.a_sub;
  auto const c_coat = tp.c_coat;

  auto const nu_hat = nu::hat( nu, a_sub, l, b );
  auto const nu_tilde = nu::tilde( nu, c_coat, l, b ) ;

  auto const F = F_tilde( nu_tilde, nu_hat, gamma, l ) ;
  auto const H = H_tilde( nu, z, F , nu_hat, nu_tilde, hp, gamma, l );
  
  auto const one = cmplx( 1. , 0. );
  auto const two = cmplx( 2. , 0. );

  auto const c1 = l * exp( - pow<2>( nu )/4 ) ;
  auto const c2 = two * nu_tilde * ( pow<2>( nu_tilde * Lambda / l ) - one );
  auto const c3 = ( nu_tilde * Lambda / l ) * exp( -z / Lambda );
  auto const c4 = H * exp( - one / Lambda ) / ( one - R0 * R1 * exp( -two/Lambda ) );
  auto const c5 = sinh( nu_tilde * z / l ) - F * cosh( nu_tilde * z / l );
  
  auto const h = ( c1 / c2 ) * ( c3 + c4 + c5 ) ;

  return h;
}

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal

