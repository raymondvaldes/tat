//
//  phases.cpp
//  tat
//
//  Created by Raymond Valdes on 10/7/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>
#include <cassert>

#include "phases.hpp"
#include "plot/gnuplot-iostream.h"
#include "units/algorithm/vector/quantity_to_value.h"
#include "algorithm/algorithm.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {
namespace plot {

using filesystem::is_directory;
using std::string;
using units::container::quantityTodouble;
using algorithm::for_each;
using std::endl;


auto phases_to_file(
  thermal::equipment::laser::Modulation_frequencies const & frequencies,
  thermal::emission::Phases const & phases,
  filesystem::path const & print_directory,
  std::string const & filename
) noexcept -> void
{
  {
    for_each( frequencies, []( auto const e ) noexcept { assert( isfinite( e ) ) ;} ) ;
    for_each( phases, []( auto const e ) noexcept { assert( isfinite( e ) ) ;} ) ;
  
    assert( frequencies.size() == phases.size() );
    assert( !frequencies.empty() );
    assert( !phases.empty() );
    assert( is_directory( print_directory ) );
    assert( !filename.empty() );
  }
  
  auto const print_dir = print_directory.string();
  auto const filePath = print_dir + "/" + filename ;
  auto const plot_eps = string( filePath + ".eps" );
  auto const data_file = string( filePath + ".txt" );
  

	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  //setup terminal
  gp << "set terminal postscript eps enhanced color font 'Helvetica,10'"<< std::endl;
  gp << "set output '" << plot_eps <<"'"<< std::endl;
  
  
  auto const x_pts = quantityTodouble( frequencies );
  auto const y_pts = quantityTodouble( phases );
  
  auto const xy_pts = make_pair( x_pts, y_pts );
  
  //set axis labels
  gp << "set xlabel 'frequency [Hz]'" << endl;
  gp << "set ylabel 'phase [rad]'" << endl;
  
  // set axis scaling
  gp << " set logscale x" << std::endl;
	gp << "plot" << gp.file1d( xy_pts, data_file  ) << std::endl;
}

} // namespace plot
} // namespace periodic
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal
