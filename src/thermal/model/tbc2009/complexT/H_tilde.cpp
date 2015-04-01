//
//  H_tilde.cpp
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "H_tilde.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{

using namespace units;
using std::complex;

auto H_tilde
(
  units::quantity< units::si::dimensionless > const nu,
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless, std::complex<double> > const F,
  units::quantity< units::si::dimensionless, std::complex<double> > const nu_hat,
  units::quantity< units::si::dimensionless, std::complex<double> > const nu_tilde,
 
  dimensionless::HeatingProperties const hp,
  units::quantity< units::si::dimensionless > const gamma,
  units::quantity< units::si::dimensionless > const l 
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  auto const Lambda = hp.Lambda;
  auto const R0 = hp.R0;
  auto const R1 = hp.R1;
  
  auto const sinhNuzl = sinh( nu_tilde * z / l ) ;
  auto const coshNuzl = cosh( nu_tilde * z / l ) ;

  auto const c1 = nu_tilde * Lambda  * R1 / l ;
  auto const c2 = R0 * exp( ( -z - 1. ) / Lambda ) + exp( ( z - 1.) / Lambda ) ;
  auto const c3 = ( 1. - R0 ) * R1 * exp( -1./ Lambda ) ;
  auto const c4 = sinhNuzl - F * coshNuzl ;
  auto const c5 = nu_tilde * coshNuzl
                / ( gamma * nu_hat * coshNuzl + nu_tilde * sinhNuzl );
  
  auto const one = std::complex<double>( 1, 0 );
  auto const two = std::complex<double>( 2, 0 );
  auto const oneD = quantity< si::dimensionless, complex<double> >( one );
  auto const twoD = quantity< si::dimensionless, complex<double> >( two );

  auto const c6 = ( ( gamma * nu_hat * Lambda ) / l + oneD ) * ( oneD + R1 ) ;
  auto const c7 = (pow<2>(nu_tilde * Lambda / l ) - oneD) * ( oneD - R1 );

  auto const H_eval = c1 * c2 - c3 * c4 + c5 * ( twoD - c6 + c7 );
  return H_eval;
}

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal
