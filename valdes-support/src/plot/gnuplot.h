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
#include <cassert>

#include "tools/interface/filesystem.hpp"
#include "gnuplot-iostream.h"
#include "units/container/quantity_to_value.h"

#include "units.h"

namespace plot {

template < typename T_x, typename T_y >
inline auto simple_XY
(
  std::vector< units::quantity< T_x > > const & X,
  std::vector< units::quantity< T_y > > const & Y
) noexcept
{
  assert( X.size() == Y.size() ) ;
  assert( X.size() > 0 ) ;

  using std::make_pair;
  using units::container::quantity_to_double;
	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  auto const x_pts = quantity_to_double( X );
  auto const y_pts = quantity_to_double( Y );
  
  auto const xy_pts = make_pair( x_pts, y_pts );
  
  gp << " set logscale x" << std::endl;
	gp << "plot" << gp.file1d( xy_pts ) << std::endl;
}

template < typename T_x, typename T_y >
inline auto simple_x_y1_y2
(
  std::vector< units::quantity< T_x > > const & X,
  std::vector< units::quantity< T_y > > const & Y1,
  std::vector< units::quantity< T_y > > const & Y2

) noexcept
{
  assert( X.size() == Y1.size() ) ;
  assert( X.size() > 0 ) ;

  using std::make_pair;
  using units::container::quantity_to_double;
	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  auto const x_pts = quantity_to_double( X );
  auto const y1_pts = quantity_to_double( Y1 );
  auto const y2_pts = quantity_to_double( Y2 );
  
  auto const xy1_pts = make_pair( x_pts, y1_pts );
  auto const xy2_pts = make_pair( x_pts, y2_pts );
  
  gp << " set logscale x" << std::endl;
	gp << "plot" << gp.file1d( xy1_pts ) << "with lines,"
            << gp.file1d( xy2_pts ) <<"with points" << std::endl;
}
  
} // namespace plot

#endif
