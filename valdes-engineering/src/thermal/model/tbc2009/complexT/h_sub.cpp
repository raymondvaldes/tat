//
//  h_sub.cpp
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "h_sub.h"
#include "h_coat.h"
#include "thermal/model/tbc2009/complexT/nu/hat.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{

using namespace units;
using std::complex;

auto h_sub
(
  units::quantity< units::si::dimensionless > const nu,
  units::quantity< units::si::dimensionless > const z,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::dimensionless > const l
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  auto const interface = quantity<si::dimensionless>(1.);
  auto const hcoat = h_coat(nu, interface , hp, tp, l );
  
  auto const b = hp.b;
  auto const a_sub = tp.a_sub;
  auto const nu_hat = nu::hat( nu, a_sub, l, b );
  auto const one =
  quantity< si::dimensionless, complex< double > >( complex< double >( 1., 0. ) );
 
  auto const h = hcoat * exp( -( z - one ) * nu_hat / (a_sub * l ) );
  
  return h;
}

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal

