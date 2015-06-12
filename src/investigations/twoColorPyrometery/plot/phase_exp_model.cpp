//
//  phase_exp_model.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "phase_exp_model.h"

#include "tools/interface/filesystem.hpp"
#include "plot/gnuplot-iostream.h"
#include "algorithm/vector/quantityTodouble.h"

namespace investigations {

namespace twoColorPyrometery {

namespace plot{

auto phase_exp_model
(
  std::vector< units::quantity< units::si::frequency > > const & x,
  std::vector< units::quantity< units::si::plane_angle > > const & y1,
  std::vector< units::quantity< units::si::plane_angle > > const & y2
) noexcept -> void
{
  assert( x.size() == y1.size() ) ;
  assert( x.size() == y2.size() ) ;
  assert( x.size() > 0 ) ;

  using std::make_pair;
  using algorithm::vector::quantityTodouble;
	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  gp << "set xlabel 'frequency (hz)'" << "\n";
  gp << "set ylabel 'phase (rad)'" << "\n";
  
  auto const x_pts = quantityTodouble( x );
  
  auto const y1_pts = quantityTodouble( y1 );
  auto const xy1_pts = make_pair( x_pts, y1_pts );

  auto const y2_pts = quantityTodouble( y2 );
  auto const xy2_pts = make_pair( x_pts, y2_pts );
  
  gp << "plot"
  << gp.file1d( xy1_pts ) << "with points title 'experimental temperature phase',"
  << gp.file1d( xy2_pts ) << "with lines title 'best-fit temperature phase'" << std::endl;
  
}

} // namespace plot
  
} // namespace twoColorPyrometery
  
} // namespace investigations
