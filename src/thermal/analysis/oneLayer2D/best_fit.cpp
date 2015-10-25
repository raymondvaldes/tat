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
  slab( disk.get_disk() ),
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

//void Best_fit::plot_model_phases_against(
//  std::vector< units::quantity< units::si::plane_angle > > const & exp_phases
//) const
//{
//  plot::simple_x_y1_y2( frequencies, model_phases, exp_phases );
//}
//
//void Best_fit::plot_model_phases_against_observations( void ) const
//{
//  assert( !frequencies.empty() );
//  assert( !model_phases.empty() );
//  assert( !observations.empty() );
//
//  assert( frequencies.size() == observations.size() ) ;
//  assert( frequencies.size() == model_phases.size() ) ;
//
//  plot::simple_x_y1_y2( frequencies, model_phases, observations );
//}

auto Best_fit::phase_goodness_of_fit_function() const -> double
{
  
  auto const gf = final_fit.phase_goodness_of_fit();
  return gf;
}

}}}


