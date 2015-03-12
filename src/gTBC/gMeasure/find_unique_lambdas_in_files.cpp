//
//  find_unique_lambdas_in_files.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include <cmath>
#include <iterator>

#include "gTBC/gMeasure/find_unique_lambdas_in_files.h"
#include "gTBC/gMeasure/sort_files_by_lambda.h"
#include "gTBC/gMeasure/unique_files_by_lambda.h"
#include "algorithm/algorithm.h"

namespace gTBC {

namespace gMeasure {

using std::vector;

using algorithm::for_each;

using units::quantity;
using units::si::wavelength;

auto
find_unique_lambdas_in_files
(
  std::vector< ScopeFile > const & scope_files
)
noexcept -> std::vector< units::quantity< units::si::wavelength > >
{
  assert( !scope_files.empty() );

  auto const sorted_files = sort_files_by_lambda( scope_files );
  auto const unique_files = unique_files_by_lambda( sorted_files );
  
  auto out =
    vector< quantity< wavelength > >();
  
  for_each( unique_files, [&out]( const auto & file )
  {
    out.push_back( file.monochorometer_lambda );
  } ) ;

  return out;
  
}

} // namespace gMeasure
  
} // namespace gTBC
