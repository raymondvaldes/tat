//
//  model_vs_experiment_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "model_vs_experiment_phases.hpp"
#include "units/container/quantity_to_value.h"
#include <utility>
#include <cassert>

namespace thermal{
namespace plot{
namespace phase{

using units::container::quantity_to_double;
using std::make_pair;

auto model_vs_experiment_phases
(
  equipment::laser::Modulation_frequencies const & frequencies,
  thermal::model::complex::Phases const & model_phases,
  thermal::model::complex::Phases const & experiment_phases
) noexcept -> void
{
  assert( model_phases.size() == experiment_phases.size() );
  assert( !model_phases.empty() );
  assert( !experiment_phases.empty() );
  assert( model_phases.size() == frequencies.size() );
  assert( experiment_phases.size() == frequencies.size() );
  
//  auto const print_dir = print_directory.string();
//  auto const filePath = print_dir + "/" + filename ;
//  auto const plot_eps = string( filePath + "_model_vs_experiment.eps" );
//  auto const data_file = string( filePath + ".txt" );
  using std::endl;

	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  //setup terminal
//  gp << "set terminal postscript eps enhanced color font 'Helvetica,10'"<< endl;
//  gp << "set output '"<< plot_eps <<"'"<< endl;
  
  
  auto const x_pts = quantity_to_double( frequencies );
  auto const y_pts = quantity_to_double( model_phases );
  auto const xy_pts = make_pair( x_pts, y_pts );

  auto const y2_pts = quantity_to_double( experiment_phases );
  auto const xy2_pts = make_pair( x_pts, y2_pts );
  
  //set axis labels
  gp << "set xlabel 'frequency [Hz]'" << endl;
  gp << "set ylabel 'phase [rad]'" << endl;
  
  //set axis scaling
  gp << " set logscale x" << endl;

  
	gp << "plot" << gp.file1d( xy_pts /*, data_file*/ ) << "with lines,"
               << gp.file1d( xy2_pts /*, data_file*/ ) <<"with points" << std::endl;


}

} // namespace phase
} // namespace plot
} // namespace thermal


