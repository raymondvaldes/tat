//
//  phase_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "phase_amplitude.h"
#include "temperature.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT {

using std::make_pair;
using namespace units;

auto phase_amplitude
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r, 
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp
) noexcept -> std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> >
{
  auto const T_complex = temperature( z, r, hp, tp );
  return make_pair( arg(T_complex), abs( T_complex ) );
}
  
} // complexT
} // tbc2009
} // model
} // thermal
