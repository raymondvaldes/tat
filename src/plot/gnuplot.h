//
//  gnuplot.h
//  tat
//
//  Created by Raymond Valdes_New on 3/15/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_gnuplot_h
#define tat_gnuplot_h

#include <vector>
#include <cmath>
#include <utility>

#include "tools/interface/filesystem.hpp"
#include "gnuplot-iostream.h"
#include "algorithm/vector/quantityTodouble.h"

#include "units.h"

namespace plot {

template < typename T_x, typename T_y >
inline auto simple_XY
(
  std::vector< units::quantity< T_x > > const & X,
  std::vector< units::quantity< T_y > > const & Y
) noexcept
{
  using std::make_pair;
  using algorithm::vector::quantityTodouble;
	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  auto const x_pts = quantityTodouble( X );
  auto const y_pts = quantityTodouble( Y );
  
  auto const xy_pts = make_pair( x_pts, y_pts );
  
  gp << " set logscale x" << std::endl;
	gp << "plot" << gp.file1d( xy_pts ) << std::endl;
}
  
} // namespace plot

#endif
