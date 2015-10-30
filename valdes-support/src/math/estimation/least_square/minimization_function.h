//
//  minimization_function.h
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef minimization_function_h_102815
#define minimization_function_h_102815

#include <functional>
#include <vector>
#include <utility>
#include <cstddef>

namespace math{
namespace estimation{
namespace least_square{


using Minimization_function = std::function < void ( double*, double* ) >;

using Minimization_function_safe =
std::function< std::vector<double>( std::vector<double> ) >;


auto prepare_minimization_function
(
  Minimization_function_safe const & minimization_function_safe
) -> std::pair< Minimization_function, size_t > ;


}}} // namespace

#endif /* minimization_function_h */
