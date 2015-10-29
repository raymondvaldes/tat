//
//  best_fit.cpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "best_fit.hpp"

#include <cassert>
#include <iostream>
#include <gsl.h>

#include "plot/gnuplot.h"
#include "statistics/uncertainty_analysis/goodness_of_fit/goodness_of_fit.h"
#include "thermal/define/lthermal.h"
#include "units.h"

using thermal::define::thermalPenetrations_from_frequencies;

namespace thermal{
namespace analysis{
namespace oneLayer2D {

Best_fit::Best_fit
(
  model::oneLayer2D::generator::Disk const & disk,
  Theoretical_results const & final_fit
) noexcept :
  engine( disk ) ,
  slab( disk.get_slab() ),
  optics( disk.get_optics() ),
  final_fit( final_fit )
{}

auto Best_fit::evaluate
(
  equipment::laser::Modulation_frequencies const & modulation_frequencies
)
const -> model::complex::Temperatures
{
  return engine.evaluate( modulation_frequencies );
}

auto Best_fit::parameters_to_string
(
  model::oneLayer2D::Parameters const & parameters
) const -> std::string
{
  Expects( !parameters.empty() );
  
  auto const s = engine.parameters_to_string( parameters );

  Ensures( !s.empty() );
  return s;
}


auto Best_fit::phase_goodness_of_fit_function() const -> double
{
  
  auto const gf = final_fit.phase_goodness_of_fit();
  return gf;
}

}}}
