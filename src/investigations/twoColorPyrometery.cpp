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
#include "thermal/model/slab/import_slab.h"

#include "units.h"

namespace investigations{

namespace twoColorPyrometery{

using gTBC::gMeasure::import_twoColor_scope_files ;
using thermal::pyrometry::twoColor::transient_analysis_sweep ;
using thermal::analysis::bulkSpeciman::temperature::diffusivity_from_phases ;
using thermal::model::slab::import ;

auto run( filesystem::directory const & dir )  -> void
{
 // temperature_prediction( dir ) ;  //prototyping function
//  phase_fitting( dir ) ;  // prototyping function
  
  calculateCalibrationCoefficients( dir ) ;

  auto const scope_data = import_twoColor_scope_files( dir,"twoColorPyro.xml" );
  auto const twoColor_data = transient_analysis_sweep( scope_data ) ;
  auto const phases = twoColor_data.phases_omega();
  auto const initial_slab = import( dir, "initial_slab.xml" ) ;

  auto const myFittedSlab = diffusivity_from_phases( phases , initial_slab );
  
  std::cout << myFittedSlab.get_diffusivity();
}

} //namespace twoColorPyrometry

} //namespace investigations
