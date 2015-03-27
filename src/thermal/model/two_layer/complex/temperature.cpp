//
//  nondimensional.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include <complex>
#include <cmath>
#include "thermal/model/two_layer/complex/temperature.h"
#include "physics/classical_mechanics/kinematics.h"

#include "math/differential/waveEquation/two_layer_system.h"
#include "thermal/model/two_layer/dimensionless/Kappa.h"
#include "thermal/model/two_layer/dimensionless/angular_frequency.h"
#include "thermal/model/two_layer/dimensionless/length.h"
#include "thermal/model/two_layer/dimensionless/a.h"
#include "thermal/model/two_layer/dimensionless/b.h"

using math::differential::waveEquation::two_layer_system;
using std::complex;
using namespace units;
using physics::classical_mechanics::frequency_to_angularFrequency;

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

auto temperature
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::frequency > const f,
  slab::Slab const & first_layer,
  slab::Slab const & second_layer,
  units::quantity< units::si::dimensionless > const R_non
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >
{
  auto const L = first_layer.characteristic_length;
  auto const alpha_1 = first_layer.get_diffusivity();
  auto const alpha_2 = second_layer.get_diffusivity();
  auto const k_1 = first_layer.get_conductivity();
  auto const k_2 = second_layer.get_conductivity();
  
  assert( L.value() > 0  );
  assert( alpha_1.value() > 0 );
  assert( alpha_2.value() > 0 );
  assert( k_1.value() > 0 );
  assert( k_2.value() > 0 );

  auto const w = frequency_to_angularFrequency( f );
  auto const x_non = dimensionless::length( x, L );
  auto const w_non = dimensionless::angular_frequency( w, L, alpha_1 ) ;
  auto const Kappa = dimensionless::Kappa( w_non ) ;
  assert( w.value() > 0 );
  assert( x_non.value() >= 0 );
  assert( w_non.value() > 0 );
  
  auto const a = dimensionless::a( alpha_1, alpha_2 ) ;
  auto const b = dimensionless::b( k_1, k_2 ) ;
  
  auto const T_solution = two_layer_system( x_non, Kappa, a, b , R_non );
 // std::cout << T_solution << "\n";
  
  using std::isfinite;
  assert( isfinite( T_solution.value().real() )  ) ;
  assert( isfinite( T_solution.value().imag() )  ) ;
  
  return T_solution;
}

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal
