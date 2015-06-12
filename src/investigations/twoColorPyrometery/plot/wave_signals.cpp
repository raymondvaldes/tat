//
//  wave_signals.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "wave_signals.h"

#include <iostream>
#include "algorithm/vector/quantityTodouble.h"
#include "algorithm/vector/ratio.h"

#include "plot/gnuplot-iostream.h"

namespace investigations {

namespace twoColorPyrometery {

namespace plot {

using std::make_pair;
using algorithm::vector::quantityTodouble;

auto wave_signals
( std::pair<
  thermal::equipment::detector::Measurements,
  thermal::equipment::detector::Measurements > const & wave_signals
)
noexcept -> void
{
	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  gp << "set term qt font \",12\"" << "\n";
  
  auto const x = wave_signals.first.referenceTimes();
  auto const y1 = wave_signals.first.signals_electical_potential();
  auto const y2 = wave_signals.second.signals_electical_potential();
  
  auto const x_pts = quantityTodouble( x );
  auto const y1_pts = quantityTodouble( y1 );
  auto const y2_pts = quantityTodouble( y2 );
  
  
  auto const xy1_pts = make_pair( x_pts, y1_pts );
  auto const xy2_pts = make_pair( x_pts, y2_pts );

  gp << "set size 1.0, 1.0"       << "\n";
  gp << "set origin 0.0, 0.0"     << "\n";
  gp << "set multiplot"           << "\n";
  
  // first plot
  gp << "set size 0.5,0.5"        << "\n";
  gp << "set origin 0.0,0.5"      << "\n";
  gp << "set grid"                << "\n";
  gp << "unset key"               << "\n";

  gp << "set title \"signal averaged wave files at:{/Symbol l}_1\""<<"\n";
  gp << "set xlabel 'time (s)'" << "\n";
  gp << "set ylabel 'detector (V)'" << "\n";
  gp << "plot"
  << gp.file1d( xy1_pts ) << "with points,"
  << std::endl;

  // second plot
  gp << "set size 0.5,0.5"        << "\n";
  gp << "set origin 0.5,0.5"      << "\n";
  gp << "set grid"                << "\n";
  gp << "unset key"               << "\n";

  gp << "set title \"signal averaged wave files at: {/Symbol l}_2\""<<"\n";
  gp << "set xlabel 'time (s)'" << "\n";
  gp << "set ylabel 'detector (V)'" << "\n";
  gp << "plot"
  << gp.file1d( xy2_pts ) << "with points,"
  << std::endl;
  
  //third plot (ratios)
  using algorithm::vector::ratio;
  auto const signal_ratios = ratio( y2_pts, y1_pts  );
  auto const xy3_pts = make_pair( x_pts, signal_ratios );
  
  gp << "set size 0.5,0.5"        << "\n";
  gp << "set origin 0.2,0.0"      << "\n";
  gp << "set grid"                << "\n";
  gp << "unset key"               << "\n";

  gp << "set title \"signal averaged wave files ratio at:  {/Symbol l}_2/{/Symbol l}_1\""<<"\n";
  gp << "set xlabel 'time (s)'" << "\n";
  gp << "set ylabel 'ratio - {/Symbol l}_2/{/Symbol l}_1 (n.d.)'" << "\n";
  gp << "plot"
  << gp.file1d( xy3_pts ) << "with points,"
  << std::endl;
  
  // close out plot
  gp << "unset multiplot" << "\n";
  
}
  
} // namespace plot
  
} // namespace twocolorPyrometery
  
} // namespace investigations
