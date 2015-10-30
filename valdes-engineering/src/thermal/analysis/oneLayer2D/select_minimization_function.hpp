//
//  select_minimization_function.hpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef select_minimization_function_hpp_102515
#define select_minimization_function_hpp_102515

#include "fit_selection.h"
#include <functional>
#include "theoretical_results.hpp"

namespace thermal{
namespace analysis{
namespace oneLayer2D{

auto select_minimization_function( Fit_selection const fit_selection )
noexcept -> std::function<
    std::function< void( const double *, double * ) >(
      std::function< Theoretical_results( const double *  ) > const &) >;

}}}

#endif /* select_minimization_function_hpp */
