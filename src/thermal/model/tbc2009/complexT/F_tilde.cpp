//
//  F_tilde.cpp
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "F_tilde.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{

using std::complex;
using namespace std::literals;
using namespace units;

auto F_tilde
(
  units::quantity< units::si::dimensionless, std::complex<double> > const nu_tilde,
  units::quantity< units::si::dimensionless, std::complex<double>  > const nu_hat,
  units::quantity< units::si::dimensionless > const gamma,
  units::quantity< units::si::dimensionless > const l
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  auto const gamma_double = gamma.value();
  auto const gamma_val = complex<double>( 0 , gamma_double  );
  auto const gamma_cplx =
  quantity< dimensionless, complex<double> >( gamma_val );
  
  auto const l_val = l.value();
  auto const l_cplx =
  quantity< dimensionless, complex<double> >( complex<double>( 0 , l_val  ) );

  auto const
  f_tilde = ( nu_tilde + nu_hat * gamma_cplx * tanh( nu_tilde / l_cplx ) )
          / ( nu_hat * gamma_cplx + nu_tilde * tanh( nu_tilde / l_cplx ) );

  return f_tilde;
}

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal
