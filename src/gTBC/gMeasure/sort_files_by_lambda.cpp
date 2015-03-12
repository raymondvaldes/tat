//
//  find_unique_lambdas_in_files.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>

#include "gTBC/gMeasure/sort_files_by_lambda.h"
#include "algorithm/algorithm.h"

namespace gTBC {

namespace gMeasure {

using std::vector;
using algorithm::find_if_not;
using algorithm::unique;
using algorithm::sort;
using units::quantity;
using units::si::wavelength;

auto
sort_files_by_lambda
(
  std::vector< ScopeFile > const & scope_files
)
noexcept -> std::vector< ScopeFile >
{
  assert( !scope_files.empty() );
  
  if( scope_files.size() == 1 ) {
    return scope_files;
  }
  
  auto sorted_files = scope_files;
  
  sort( sorted_files, [](auto const & a, auto const & b)
  {
    return a.monochorometer_lambda.value() < b.monochorometer_lambda.value() ;
  } ) ;
  
  return sorted_files;
}

} // namespace gMeasure
  
} // namespace gTBC
