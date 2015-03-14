//
//  2colorPyrometery.cpp
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//
#include <iostream>
#include <cassert>

#include "investigations/twoColorPyrometery/calculateCalibrationCoefficients.h"
#include "investigations/twoColorPyrometery/temperature_prediction.h"
#include "investigations/twoColorPyrometery/phase_fitting.h"

#include "gTBC/gMeasure/import_twoColor_scope_files.h"
#include "thermal/pyrometry/twoColor/transient_analysis_sweep.h"
#include "thermal/analysis/bulkSpeciman/temperature/conductivity_from_phases.h"

#include "units.h"


namespace investigations{

namespace twoColorPyrometery{

using gTBC::gMeasure::import_twoColor_scope_files;
using thermal::pyrometry::twoColor::transient_analysis_sweep;
using thermal::analysis::bulkSpeciman::temperature::diffusivity_from_phases;

using thermal::model::slab::Slab;
using units::quantity;
using units::si::thermal_conductivity;
using units::si::length;
using units::si::micrometers;
using units::si::kelvin;
using units::si::square_millimeters;
using units::si::watts;
using units::si::second;
using units::si::thermal_diffusivity;
using units::si::meter;

auto run( filesystem::directory const & dir )  -> void
{
 // temperature_prediction( dir ) ;  //prototyping function
//  phase_fitting( dir ) ;  // prototyping function
  
  calculateCalibrationCoefficients( dir ) ;
  
  auto const scope_data = import_twoColor_scope_files( dir ) ;
  auto const temperature_info = transient_analysis_sweep( scope_data ) ;
  
//  auto const initial_slab = import_initial_slab( dir, "initial_slab.xml" );
  auto const k = quantity< thermal_conductivity >( 120.1  * watts / ( meter * kelvin ) );
  auto const characteristic_length = quantity< length >( 1420 * micrometers );
  auto const alpha = quantity<thermal_diffusivity>( 5 * square_millimeters / second );
  auto const mySlab_off = Slab{ characteristic_length, alpha, k };

  temperature_info.phases_omega();
  
//  auto const myFittedSlab =
//  diffusivity_from_phases( , mySlab_off );
  
//  std::cout << myFittedSlab.get_diffusivity();
}

} //namespace twoColorPyrometry

} //namespace investigations
