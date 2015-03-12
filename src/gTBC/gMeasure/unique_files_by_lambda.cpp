//
//  unique_files_by_lambda.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <cmath>

#include "gTBC/gMeasure/unique_files_by_lambda.h"
#include "algorithm/algorithm.h"

namespace gTBC {

namespace gMeasure {

using algorithm::unique;
using std::abs;

auto
unique_files_by_lambda
(
  std::vector< ScopeFile > const & sorted_files
)
noexcept -> std::vector< ScopeFile >
{
  auto const unique_files = unique( sorted_files,
  []( auto const & a, auto const & b ) noexcept
  {
    auto const lhs = a.monochorometer_lambda.value() ;
    auto const rhs = b.monochorometer_lambda.value() ;
    auto const tolerance = 1e-10;
    auto const not_unique = abs( lhs - rhs ) < tolerance ;
    return not_unique ;
  });
  
  return unique_files;
}

} // namespace gMeasure
  
} // namespace gTBC
