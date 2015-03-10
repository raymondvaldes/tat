//
//  phase_fitting.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>

#include "investigations/twoColorPyrometery/phase_fitting.h"
#include "thermal/model/slab/slab.h"
#include "thermal/define/lthermal.h"
#include "physics/classical_mechanics/kinematics.h"
#include "units.h"

namespace investigations {

namespace twoColorPyrometery {

auto phase_fitting( filesystem::directory const & dir ) -> void
{
  using units::quantity;
  using units::si::length;
  using units::si::micrometers;
  using units::si::watts;
  using units::si::area;
  using units::si::square_meter;
  using units::si::thermal_conductivity;
  using units::si::thermal_conductivity_units;
  using units::si::thermal_diffusivity;
  using units::si::thermal_diffusivity_units;
  using units::si::hertz;
  using units::si::second;
  using units::si::heat_flux;
  using units::si::frequency;
  using units::si::kelvin;
  using units::si::meter;
  
  auto const x = quantity< length >( 273 * micrometers );
  
  auto const I_transient = quantity< heat_flux >( 260 * watts / square_meter );
  
  auto const k = quantity< thermal_conductivity >( 10.7  * watts / ( meter * kelvin ) );
  
  auto const characteristic_length = quantity< length >(1200 * micrometers );
  
  auto const alpha = quantity<thermal_diffusivity>(23 * square_meter / second);
  
  auto const f = quantity< frequency >( 23 * hertz );
  
  using physics::classical_mechanics::frequency_to_angularFrequency;
  auto const w = frequency_to_angularFrequency( f ) ;

  using thermal::define::thermal_penetration;
  auto const l = thermal_penetration( alpha, w, characteristic_length ) ;


  using thermal::model::slab::temperature_phase;
  temperature_phase(x, w, characteristic_length, alpha, I_transient, k );



}
  
} // namespace twoColorPyrometery
  
} // namespace investigations
