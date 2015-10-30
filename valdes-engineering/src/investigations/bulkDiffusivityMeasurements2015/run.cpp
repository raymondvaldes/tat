//
//  run.cpp
//  tat
//
//  Created by Raymond Valdes on 9/8/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//
#include "run.hpp"

#include <cassert>
#include <iostream>
#include "units.h"

#include "beamExpander/sept4/fit_models.hpp"
#include "beamExpander/sept22/fit_models.h"
#include "beamExpander/heated_stage/sept23/fit_models.h"
#include "beamExpander/adiabatic_rear/aluminum_target/sept24/fit_models.h"
#include "beamExpander/adiabatic_rear/poco_edm3/fit_models.h"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{

using namespace units;

auto run( filesystem::directory const & /*dir*/ ) noexcept -> void
{
  use_engineering_prefix();

//  beamExpander::sept4::fit_models();
//  beamExpander::sept22::fit_models();
//  beamExpander::heated_stage::sept23::fit_models();
//  beamExpander::adiabatic_rear::aluminum_target::sept24::fit_models();
  beamExpander::adiabatic_rear::poco_edm3::fit_models();
  
  std::cout << "\n'Raymond, you can do anything!!' - Melissa Mejia\n";
  std::cout << "\n'All of me loves all of you!' - Melissa Mejia\n";
}

} // namespace bulkDiffusivityMeasurements2015
} // namespace investigations
