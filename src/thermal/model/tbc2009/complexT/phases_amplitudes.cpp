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
using algorithm::transform;
using namespace units;

auto phases_amplitudes
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r, 
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  std::vector< units::quantity< units::si::dimensionless > > const ls
) noexcept -> std::vector< std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> > >
{
  auto info = vector< pair< quantity< plane_angle >,
                            quantity< si::dimensionless > > >( ls.size() );
  transform( ls , info.begin(), [&]( auto const & l) noexcept
  {
    return phase_amplitude( z, r, hp, tp, l );
  } ) ;

  return info;
}
  
} // complexT
} // tbc2009
} // model
} // thermal
