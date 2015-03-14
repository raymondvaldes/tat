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
#include "thermal/analysis/bulkSpeciman/temperature/conductivity_from_phases.h"
#include "math/random/random.h"
#include "math/construct/range.h"
#include "units.h"

namespace investigations {

namespace twoColorPyrometery {

auto phase_fitting( filesystem::directory const & dir ) -> void
{
  using units::quantity;
  using units::si::dimensionless;
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
  using units::si::radians;
  using units::si::plane_angle;
  using units::si::square_millimeters;
  
//  auto const x = quantity< length >( 273 * micrometers );
//  auto const I_transient = quantity< heat_flux >( 260 * watts / square_meter );
  
  auto const k = quantity< thermal_conductivity >( 120.1  * watts / ( meter * kelvin ) );
  
  auto const characteristic_length = quantity< length >( 1420 * micrometers );

  auto const alpha = quantity<thermal_diffusivity>( 5 * square_millimeters / second );

  using thermal::model::slab::Slab;
  auto mySlab = Slab{ characteristic_length, alpha, k };
  
  using physics::classical_mechanics::frequency_to_angularFrequency;




  using math::construct::range_1og10;
  auto const lmin = quantity< dimensionless >( 0.02 );
  auto const lmax = quantity< dimensionless >( 1. );
  auto const lthermalSize = 20;
  auto const lthermals = range_1og10( lmin, lmax, lthermalSize );

  using thermal::define::angularFrequencies_from_thermalPenetrations;
  using thermal::define::frequencies_from_thermalPenetrations;
  
  auto const omegas =
  angularFrequencies_from_thermalPenetrations( lthermals, alpha, characteristic_length ) ;
  
  auto const frequencies =
  frequencies_from_thermalPenetrations( lthermals, alpha, characteristic_length  );
  
  using thermal::model::slab::surface_temperature_phases;
  auto const initial_phases = surface_temperature_phases( frequencies, mySlab );
  
  using math::addNoise;
  auto const std_error_percent = quantity<dimensionless>( 0.01 ) ;
  auto const std_error_scale = quantity< plane_angle >( M_PI_2 * radians );
  auto const experimental_phases =
    addNoise( initial_phases, std_error_percent, std_error_scale );
  
  auto const alpha_initial = quantity<thermal_diffusivity >( 5 * square_millimeters / second);
  auto mySlab_off = Slab{ characteristic_length,alpha_initial , k };

  for( size_t i = 0 ; i < experimental_phases.size() ; ++i )
    std::cout << initial_phases[i].value() << "\t" << experimental_phases[i].value() << "\n" ;

 
  using thermal::analysis::bulkSpeciman::temperature::diffusivity_from_phases;
  auto const myFittedSlab =
    diffusivity_from_phases( omegas, experimental_phases, mySlab_off );

  std::cout << myFittedSlab.get_diffusivity() << "\t" ;



/*
  Parameter Estimation algorithm complete....
 
  Fitting phases
  --------------
  Inputs:
  - Initial slab
  - experimental phases
  
  - predicted alpha ( only parameter that is possible to extract,
                      keep everything else constant )
  - predicted phases
 
  Fitting amplitudes
  ------------------
  Inputs:
  - Initial slab
  - experimental amplitudes
  - predicted I_transient ( only parameter that is possible to extract 
                            assuming k is already known )
  - predicted phases
  
  FItting amplitude is good because it gives me what I_transient is....
*/

}
  
} // namespace twoColorPyrometery
  
} // namespace investigations
