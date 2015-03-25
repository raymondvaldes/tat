//
//  nondimensional.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <complex>
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
  slab::Slab const & second_layer
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >
{
  auto const L = first_layer.characteristic_length;
  auto const alpha_1 = first_layer.get_diffusivity();
  auto const alpha_2 = second_layer.get_diffusivity();
  auto const k_1 = first_layer.get_conductivity();
  auto const k_2 = second_layer.get_conductivity();

  auto const w = frequency_to_angularFrequency( f );
  auto const x_non = dimensionless::length( x, L );
  auto const w_non = dimensionless::angular_frequency( w, L, alpha_1 ) ;
  auto const Kappa = dimensionless::Kappa( w_non ) ;
  
  auto const a = dimensionless::a( alpha_1, alpha_2 ) ;
  auto const b = dimensionless::b( k_1, k_2 ) ;
  
  auto const T_solution = two_layer_system( x_non, Kappa, a, b );
  return T_solution;
}

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal
