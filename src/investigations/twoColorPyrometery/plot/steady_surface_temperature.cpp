//
//  steady_surface_temperature.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "steady_surface_temperature.h"

#include <utility>
#include <iostream>
#include "algorithm/vector/quantityTodouble.h"
#include "plot/gnuplot-iostream.h"

namespace investigations {

namespace twoColorPyrometery {

namespace plot {

using std::make_pair;
using algorithm::vector::quantityTodouble;

auto steady_surface_temperature(
  std::vector< units::quantity< units::si::frequency > > const & x,
  std::vector< units::quantity< units::si::temperature > > const & y1
) noexcept -> void
{
  assert( x.size() == y1.size() ) ;
  assert( x.size() > 0 ) ;

	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  gp << "set xlabel 'frequency (hz)'" << "\n";
  gp << "set ylabel 'temperature (K)'" << "\n";
  
  auto const x_pts = quantityTodouble( x );
  auto const y1_pts = quantityTodouble( y1 );
  
  auto const xy1_pts = make_pair( x_pts, y1_pts );

  gp << "plot"
  << gp.file1d( xy1_pts ) << "with points title 'steady state temperature',"
  << std::endl;
}
  
} // namespace plot

} // namespace twoColorPyrometery
  
} // namespace investigations
