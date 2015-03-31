//
//  phases_amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "phases_amplitudes.h"
#include "thermal/model/tbc2009/complexT/phase_amplitude.h"
#include "algorithm/algorithm.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT {

using std::pair;
using std::vector;
using std::transform;
using namespace units;

auto phases_amplitudes
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r, 
  std::vector< dimensionless::HeatingProperties > const & hps,
  dimensionless::ThermalProperties const tp
) noexcept -> std::vector< std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> > >
{
  auto info = vector< pair< quantity< plane_angle >,
                            quantity< si::dimensionless > > >( hps.size() );
  transform( hps.begin(), hps.end() , info.begin(), [&]( auto const & hp) noexcept
  {
    return phase_amplitude( z, r, hp, tp );
  } ) ;

  return info;
}
  
} // complexT
} // tbc2009
} // model
} // thermal
