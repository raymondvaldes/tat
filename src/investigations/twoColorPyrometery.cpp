//
//  2colorPyrometery.cpp
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//
#include <cassert>
#include <iostream>
#include "units.h"

#include "investigations/twoColorPyrometery.h"

#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all/diffusivity_from_phases.h"
#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_laser/diffusivity_from_phases.h"
#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_diffusivity/diffusivity_from_phases.h"
#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_detectorRadius/diffusivity_from_phases.h"
#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/uncertainty_analysis.h"

#include "investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/avg_phases_at_surface.h"
#include "investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/surface_phases_at_radial_position.h"
#include "investigations/twoColorPyrometery/oneLayer2D/temp_sweep/surface_radial_profile.h"
#include "investigations/twoColorPyrometery/oneLayer2D/amplitude_analysis/amplitudes_from_experiment.h"
#include "investigations/twoColorPyrometery/oneLayer2D/complex_temperature_check/complex_temperature_check.h"
#include "investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/surface_phases_with_beam_diameter.h"

#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_a_offset/fit_all/fit.h"
#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_a_b1_b2_b3/fit_all/fit.hpp"
#include "investigations/twoColorPyrometery/oneLayer2D/calculators/thermal_penetration/lthermal_at_frequency.hpp"

namespace investigations{
namespace twoColorPyrometery{

auto run( filesystem::directory const & dir ) noexcept -> void
{
//  oneLayer2D::phase_analysis::fit_all_but_laser::diffusivity_from_phases(dir);


//  oneLayer2D::phase_analysis::fit_a_offset::fit_all::fit(dir); // a_offset
//    oneLayer2D::phase_analysis::fit_all::diffusivity_from_phases(dir);

//    oneLayer2D::phase_analysis::fit_a_b1_b2_b3::fit_all::fit( dir ) ;
  
  
 
 // oneLayer2D::phase_analysis::fit_all_but_diffusivity::diffusivity_from_phases(dir);
//  oneLayer2D::phase_analysis::fit_all_but_detectorRadius::diffusivity_from_phases(dir);
//  oneLayer2D::phase_analysis::uncertainty_analysis( dir );
  
//  oneLayer2D::complex_temperature_check::complex_temperature_check( dir );

  

  // sweeps and profiles
//  oneLayer2D::frequency_sweep::surface_phases_with_beam_diameter(dir);
//  oneLayer2D::temp_sweep::surface_radial_profile( dir );

  oneLayer2D::frequency_sweep::avg_phases_at_surface(dir);

//
//  oneLayer2D::amplitude_analysis::amplitudes_from_experiment(dir);
//  oneLayer2D::frequency_sweep::surface_phases_at_radial_position(dir);



//calculators
//  oneLayer2D::calculators::thermal_penetration::lthermal_at_frequency(dir);
}

} //namespace twoColorPyrometry
} //namespace investigations
