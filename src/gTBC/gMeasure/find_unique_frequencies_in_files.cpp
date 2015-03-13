//
//  find_unique_frequencies_in_files.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include <algorithm>

#include "gTBC/gMeasure/find_unique_frequencies_in_files.h"
#include "algorithm/algorithm.h"

namespace gTBC {

namespace gMeasure {

using std::vector;

using algorithm::for_each;
using algorithm::sort;
using algorithm::unique;

using units::quantity;
using units::si::frequency;

auto
find_unique_frequencies_in_files
(
  std::vector< ScopeFile > const & scope_files
)
noexcept ->
 std::pair< std::vector< ScopeFile >,
 std::vector< units::quantity< units::si::frequency > > >
{
  assert( !scope_files.empty() );

  auto const sorted_files = sort( scope_files, sort_frequency_predicate ) ;
  auto const unique_files = unique( sorted_files, unique_frequency_predicate );
  
  auto out = vector< quantity< frequency > >();
  
  for_each( unique_files, [&out]( const auto & file )
  {
    out.push_back( file.laser_modulation_frequency );
  } ) ;

  return make_pair( unique_files, out );
}

} // namespace gMeasure
  
} // namespace gTBC
