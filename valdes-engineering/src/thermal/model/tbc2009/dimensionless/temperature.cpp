//
//  temperature.cpp
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "temperature.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

using std::complex;
using namespace units;

auto temperature
(
  units::quantity< units::si::dimensionless, std::complex<double>  > const theta,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::heat_flux > const I_o,
  units::quantity< units::si::dimensionless > const R0,
  units::quantity< units::si::thermal_conductivity > const k_coat
) noexcept -> units::quantity< units::si::temperature, std::complex<double> >
{
  auto const ref_real = L * I_o * ( 1.- R0 ) / k_coat;
  auto const ref_cmpl = complex<double>( ref_real.value() , 0. );

  auto const reference_cmplx =
  quantity< si::one_over_temperature, complex<double> >::from_value(ref_cmpl);
  
  auto const t_dim = theta / reference_cmplx;
  
  return t_dim;
}

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

