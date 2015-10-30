//
//  phase_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "phase_amplitude.h"
#include "temperature.h"
#include "math/coordinate_system/wrap_to_negPi_posPi.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT {

using std::make_pair;
using namespace units;
using math::coordinate_system::wrap_to_negPi_posPi;

auto phase_amplitude
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r, 
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::dimensionless > const l
) noexcept -> std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> >
{
  auto const T_complex = temperature( z, r, hp, tp, l );
  
  auto const phase = arg( T_complex ) - M_PI_2 * radians ;

  auto const phase_wrapper = wrap_to_negPi_posPi( phase );

  return make_pair( phase_wrapper , abs( T_complex ) );
}
  
} // complexT
} // tbc2009
} // model
} // thermal
