//
//  select_minimization_function.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "select_minimization_function.hpp"
#include "amplitude_analysis/make_minimization_equation.hpp"
#include "phase_analysis/make_minimization_equation.hpp"

namespace thermal{
namespace analysis{
namespace oneLayer2D{

auto select_minimization_function( Fit_selection const fit )
noexcept -> std::function<
    std::function< void( const double *, double * ) >(
      std::function< Theoretical_results( const double *  ) > const &) >
{
  auto fun = std::function<
    std::function< void( const double *, double * ) >(
      std::function< Theoretical_results( const double *  ) > const &) >();

  switch( fit )
  {
    case Fit_selection::phases:
      fun = phase_analysis::minimization_equation;
      break;
    
    case Fit_selection::amplitudes:
      fun = amplitude_analysis::minimization_equation;
      break;
  }

  return fun;
}


}}}
