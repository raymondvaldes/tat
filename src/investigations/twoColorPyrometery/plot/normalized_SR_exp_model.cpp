//
//  normalized_SR_exp_model.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "normalized_SR_exp_model.h"

#include "tools/interface/filesystem.hpp"
#include "plot/gnuplot-iostream.h"
#include "units/container/quantity_to_value.h"

namespace investigations {

namespace twoColorPyrometery {

namespace plot{

auto normalized_SR_exp_model
(
  std::vector< units::quantity< units::si::time > > const & x,
  std::vector< units::quantity< units::si::one_over_temperature > > const & y1,
  std::vector< units::quantity< units::si::one_over_temperature > > const & y2
) noexcept -> void
{
  assert( x.size() == y1.size() ) ;
  assert( x.size() == y2.size() ) ;
  assert( x.size() > 0 ) ;

  using std::make_pair;
  using units::container::quantity_to_double;
	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  gp << "set xlabel 'time (s)'" << "\n";
  gp << "set ylabel 'normalized signal ratio (1/K)'" << "\n";
  
  auto const x_pts = quantity_to_double( x );
  
  auto const y1_pts = quantity_to_double( y1 );
  auto const xy1_pts = make_pair( x_pts, y1_pts );

  auto const y2_pts = quantity_to_double( y2 );
  auto const xy2_pts = make_pair( x_pts, y2_pts );
  
  gp << "plot"
  << gp.file1d( xy1_pts ) << "with points title 'experimental SR_norm',"
  << gp.file1d( xy2_pts ) << "with lines title 'best-fit SR_norm'" << std::endl;
}

} // namespace plot
  
} // namespace twoColorPyrometery
  
} // namespace investigations
