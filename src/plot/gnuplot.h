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

inline auto hello_world( void ) -> void
{
	Gnuplot gp("/usr/local/bin/gnuplot --persist");

	std::vector<std::pair<double, double> > xy_pts_A;
	for(double x=-2; x<2; x+=0.01) {
		double y = x*x*x;
		xy_pts_A.push_back(std::make_pair(x, y));
	}

	std::vector<std::pair<double, double> > xy_pts_B;
	for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
		double theta = alpha*2.0*3.14159;
		xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
	}

  gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).
	gp << "plot" << gp.file1d(xy_pts_A, "myRaymond.data") << "with lines title 'cubic',"
		<< gp.file1d(xy_pts_B) << "with points title 'circle'" << std::endl;
  
  gp << "set term png"  << "\n";
  gp << "set output \"/Users/raymondvaldes/printme.png\""  << "\n";
  gp << "replot"  << "\n";
}

  
} // namespace plot

#endif
