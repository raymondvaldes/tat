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
#include "plot/gnuplot.h"

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

  auto const bestFit_results = diffusivity_from_phases( phases , initial_slab );
 
  std::cout << bestFit_results.fitted_slab.get_diffusivity() << "\n";

  for( size_t i = 0; i < bestFit_results.bestFit_phases.size(); ++i )
  {
    std::cout
    << twoColor_data.laser_modulation_freq[i]
    << "\t" << twoColor_data.surface_steady_temperature()[i]
    << "\t" << phases.first[i]
    << "\t" << bestFit_results.experimenta_phases[i]
    << "\t" << bestFit_results.bestFit_phases[i] << "\n";
  }
  
  
  ///List of things that could be wrong!
  // Boundary conditions are not properly specified for my equation
  
  // the theoretical equation yields a phase that is off by pi and this may
  // be giving incorrect results
  
  // the experimental phase and amplitude is incorrectly reported due to
  // poor fitting of a cosine wave - verify that teh fit is good by having a
  // minimum threshold for the R^2 of the fit
  
  // The signal averaging failed - need to check this by calculating the signal
  // to noise ratio before and after signal averaging
  
//  plot::hello_world();
}

} //namespace twoColorPyrometry

} //namespace investigations
