//
//  model_vs_experiment_amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes on 10/27/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "model_vs_experiment_amplitudes.hpp"
#include "units/container/quantity_to_value.h"

#include <utility>
#include <gsl.h>

namespace thermal{
namespace plot{
namespace amplitudes{

using units::container::quantity_to_double;
using std::make_pair;

auto model_vs_experiment_amplitudes
(
  equipment::laser::Modulation_frequencies const & frequencies,
  thermal::model::complex::Amplitudes const & model,
  thermal::model::complex::Amplitudes const & experiment
) noexcept -> void
{
  Expects( model.size() == experiment.size() );
  Expects( !model.empty() );
  Expects( !experiment.empty() );
  Expects( model.size() == frequencies.size() );
  Expects( experiment.size() == frequencies.size() );
  
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
  auto const y_pts = quantity_to_double( model );
  auto const xy_pts = make_pair( x_pts, y_pts );

  auto const y2_pts = quantity_to_double( experiment );
  auto const xy2_pts = make_pair( x_pts, y2_pts );
  
  //set axis labels
  gp << "set xlabel 'frequency [Hz]'" << endl;
  gp << "set ylabel 'amplitude [K]'" << endl;
  
  //set axis scaling
  gp << " set logscale x" << endl;
  gp << " set logscale y" << endl;

  
	gp << "plot" << gp.file1d( xy_pts /*, data_file*/ ) << "with lines,"
               << gp.file1d( xy2_pts /*, data_file*/ ) <<"with points" << std::endl;

}

} // namespace ammplitudes
} // namespace plot
} // namespace thermal


