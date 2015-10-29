//
//  transient_surface_amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "transient_surface_amplitudes.h"

#include <utility>
#include <iostream>
#include "units/container/quantity_to_value.h"
#include "plot/gnuplot-iostream.h"

namespace investigations {
namespace twoColorPyrometery {
namespace plot {

using std::make_pair;
using units::container::quantity_to_double;

auto transient_surface_amplitudes(
  std::vector< units::quantity< units::si::frequency > > const & x,
  std::vector< units::quantity< units::si::temperature > > const & y1
) noexcept -> void
{
  assert( x.size() == y1.size() ) ;
  assert( x.size() > 0 ) ;

	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  gp << "set xlabel 'frequency (hz)'" << "\n";
  gp << "set ylabel 'temperature (K)'" << "\n";
  
  auto const x_pts = quantity_to_double( x );
  auto const y1_pts = quantity_to_double( y1 );
  
  auto const xy1_pts = make_pair( x_pts, y1_pts );

  gp << "plot"
  << gp.file1d( xy1_pts ) << "with points title 'transient surface amplitudes',"
  << std::endl;
}
  
} // namespace plot
} // namespace twoColorPyrometery
} // namespace investigations
