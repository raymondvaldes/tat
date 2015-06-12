//
//  results.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/periodic/results.h"
#include "plot/gnuplot-iostream.h"
#include "algorithm/vector/quantityTodouble.h"

using algorithm::vector::quantityTodouble;

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

auto transient_analysis_results::plot_normalized_SR_exp_model( void )
const noexcept -> void
{
  
	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  gp << "set xlabel 'time (s)'" << "\n";
  gp << "set ylabel 'normalized signal ratio (1/K)'" << "\n";
  
  auto const x_pts = quantityTodouble( normalized_SRs.first );
  
  auto const y1_pts = quantityTodouble( normalized_SRs.second );
  auto const xy1_pts = make_pair( x_pts, y1_pts );
  
  auto shifted_cosine = fitted_cosine_function;
  shifted_cosine.shift_phase( laser_modulation_phase );
  auto const y2 = shifted_cosine.evaluate( normalized_SRs.first );
  auto const y2_pts = quantityTodouble( y2 );
  auto const xy2_pts = make_pair( x_pts, y2_pts );
  
  
  using units::quantity_to_string;
  gp  << "set label \"T_{steady} ="    << steady_temperature.value()
      << "[K] \" at 2,0.001739" << "\n";
  
  gp  << "set label \"T_{phase} ="     << transient_temperature_phase.value()
      << "[K] \" at 2,0.001738" << "\n";
  
  gp  << "set label \"T_{transient} =" << transient_temperature_amplitude.value()
      << "[K] \" at 2,0.001737" << "\n";
  
  gp  << "set label \"frequency =" << laser_modulation_w.value() / (2*M_PI)
      << "[hz]\" at 2,0.001736" << "\n";

  
  gp << "plot"
  << gp.file1d( xy1_pts ) << "with points title 'experimental SR_{norm}',"
  << gp.file1d( xy2_pts ) << "with lines title 'best-fit SR_{norm}'" << std::endl;
  
  // add labels
}

} // namespace periodic
} // namespace twoColor
} // namespace napyrometryme
} // namespace thermal


