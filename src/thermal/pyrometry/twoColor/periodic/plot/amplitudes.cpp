//
//  amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes on 10/7/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>

#include "amplitudes.hpp"
#include "plot/gnuplot-iostream.h"
#include "units/algorithm/vector/quantity_to_value.h"
#include "algorithm/algorithm.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {
namespace plot {

using std::string;
using filesystem::is_directory;
using units::container::quantityTodouble;
using algorithm::for_each;
using units::isfinite;
using std::endl;

auto amplitudes_to_file_log_linear(
  thermal::equipment::laser::Modulation_frequencies const & frequencies,
  Temperature_amplitudes const & amplitudes,
  filesystem::path const & print_directory,
  std::string const & filename  
) noexcept -> void
{
  {
    for_each( frequencies, []( auto const e ) noexcept { assert( isfinite( e ) ) ;} ) ;
    for_each( amplitudes, []( auto const e ) noexcept { assert( isfinite( e ) ) ;} ) ;
  
    assert( frequencies.size() == amplitudes.size() );
    assert( !frequencies.empty() );
    assert( !amplitudes.empty() );
    assert( is_directory( print_directory ) );
    assert( !filename.empty() );
  }
  auto const print_dir = print_directory.string();
  auto const filePath = print_dir + "/" + filename ;
  auto const plot_eps = string( filePath + "_loglinear.eps" );
  auto const data_file = string( filePath + ".txt" );
  

	Gnuplot gp("/usr/local/bin/gnuplot");
  
  //setup terminal
  gp << "set terminal postscript eps enhanced color font 'Helvetica,10'"<< endl;
  gp << "set output '"<< plot_eps <<"'"<< endl;
  
  
  auto const x_pts = quantityTodouble( frequencies );
  auto const y_pts = quantityTodouble( amplitudes );
  
  auto const xy_pts = make_pair( x_pts, y_pts );
  
  //set axis labels
  gp << "set xlabel 'frequency [Hz]'" << endl;
  gp << "set ylabel 'amplitude [K]'" << endl;
  
  //set axis scaling
  gp << " set logscale x" << endl;

	gp << "plot" << gp.file1d( xy_pts, data_file  ) << endl;
}


auto amplitudes_to_file_log_log(
  thermal::equipment::laser::Modulation_frequencies const & frequencies,
  Temperature_amplitudes const & amplitudes,
  filesystem::path const & print_directory,
  std::string const & filename  
) noexcept -> void
{
  {
    for_each( frequencies, []( auto const e ) noexcept { assert( isfinite( e ) ) ;} ) ;
    for_each( amplitudes, []( auto const e ) noexcept { assert( isfinite( e ) ) ;} ) ;
  
    assert( frequencies.size() == amplitudes.size() );
    assert( !frequencies.empty() );
    assert( !amplitudes.empty() );
    assert( is_directory( print_directory ) );
    assert( !filename.empty() );
  }
  
  auto const print_dir = print_directory.string();
  auto const filePath = print_dir + "/" + filename ;
  auto const plot_eps = string( filePath + "_loglog.eps" );
  auto const data_file = string( filePath + ".txt" );
  

	Gnuplot gp("/usr/local/bin/gnuplot");
  
  //setup terminal
  gp << "set terminal postscript eps enhanced color font 'Helvetica,10'"<< endl;
  gp << "set output '"<< plot_eps <<"'"<< endl;
  
  
  auto const x_pts = quantityTodouble( frequencies );
  auto const y_pts = quantityTodouble( amplitudes );
  
  auto const xy_pts = make_pair( x_pts, y_pts );
  
  //set axis labels
  gp << "set xlabel 'frequency [Hz]'" << endl;
  gp << "set ylabel 'amplitude [K]'" << endl;

  //set axis scaling
  gp << " set logscale x" << endl;
  gp << " set logscale y" << endl;

	gp << "plot" << gp.file1d( xy_pts, data_file  ) << endl;
}

} // namespace plot
} // namespace periodic
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal



