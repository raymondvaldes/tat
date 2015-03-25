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
#include "thermal/model/slab/slab.h"

#include "units.h"

#include "plot/gnuplot.h"
#include "investigations/twoColorPyrometery/plot/phase_exp_model.h"
#include "investigations/twoColorPyrometery/plot/steady_surface_temperature.h"
#include "investigations/twoColorPyrometery/plot/transient_surface_amplitudes.h"
#include "investigations/twoColorPyrometery/plot/wave_signals.h"

#include "thermal/model/two_layer/complex/surface_phases.h"
#include "thermal/analysis/two_layer_speciman/diffusivity_from_phases.h"

namespace investigations{

namespace twoColorPyrometery{

using gTBC::gMeasure::import_twoColor_scope_files ;

using thermal::pyrometry::twoColor::transient_analysis_sweep ;
using thermal::analysis::bulkSpeciman::temperature::diffusivity_from_phases ;
using thermal::analysis::two_layer_speciman::diffusivity_from_phases;
using thermal::model::slab::import ;
using algorithm::for_each;

auto run( filesystem::directory const & dir ) -> void
{
  auto const gCoeff = calculateCalibrationCoefficients( dir ) ;
  std::cout << gCoeff << "\n";
  
  auto const scope_data = import_twoColor_scope_files( dir, "twoColorPyro.xml" , gCoeff );
  plot::wave_signals( scope_data.measurements.front()  );
  plot::wave_signals( scope_data.measurements.back()  );

  auto const twoColor_data = transient_analysis_sweep( scope_data ) ;
  
  auto const initial_slab = import( dir, "initial_slab.xml" ) ;
  auto const substrate_slab = import( dir, "substrate_slab.xml" ) ;

  
  //auto const BC = thermal::model::slab::back_boundary_condition::T_base;
//  auto const bestFit_results =
//  diffusivity_from_phases( twoColor_data.phases_omega() , initial_slab , BC);
  
  auto const bestFit_results =
  diffusivity_from_phases( twoColor_data.phases_frequency() , initial_slab, substrate_slab ) ;
  
  std::cout << bestFit_results.fitted_slab.get_diffusivity() << "\n";
 
  plot::phase_exp_model
  (
    bestFit_results.frequencies,
    bestFit_results.experimenta_phases,
    bestFit_results.bestFit_phases
  );
  
  plot::transient_surface_amplitudes(
      bestFit_results.frequencies ,
      twoColor_data.surface_temperature_amplitudes()
  );
  
  plot::steady_surface_temperature(
    bestFit_results.frequencies ,
    twoColor_data.surface_steady_temperature());
  
  twoColor_data.transient_results.back().plot_normalized_SR_exp_model();
  twoColor_data.transient_results.front().plot_normalized_SR_exp_model();
}

} //namespace twoColorPyrometry

} //namespace investigations
