//
//  planks_law.cpp
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/emission/planks_law/planks_law.h"
#include "units/si/constants/thermal.h"
#include <cassert>

using units::si::constants::C1_wien;
using units::si::constants::C2_wien;
using namespace units;

namespace thermal {
namespace emission {
namespace monochromatic_blackbody_emissive_power {

auto planks_law
(
  units::quantity< units::si::temperature > const absolute_temperature,
  units::quantity< units::si::wavelength > const emissive_wavelength
)
noexcept -> units::quantity< units::si::heat_flux_over_length >
{
  // monochromatic blackbody emissive power
  
  assert( absolute_temperature > 0 * kelvin );
  assert( emissive_wavelength > 0 * meters);
  
  auto const T = absolute_temperature;
  auto const lambda = emissive_wavelength;
  
  auto const I_lambda =
  ( C1_wien / pow<5>( lambda ) ) * pow<-1>( exp( C2_wien / ( lambda * T ) ) - 1. ) ;

  return I_lambda;
}

}
} // namespace emission
} // namespace thermal
