//
//  find_unique_labels_in_files.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include <algorithm>

#include "gTBC/gMeasure/find_unique_labels_in_files.h"
#include "algorithm/algorithm.h"

namespace gTBC {

namespace gMeasure {

using std::vector;
using std::string;

using algorithm::for_each;
using algorithm::sort;
using algorithm::unique;

auto
find_unique_labels_in_files
(
  std::vector< ScopeFile > const & scope_files
)
noexcept -> std::pair< std::vector< ScopeFile >, std::vector< std::string > >
{
  assert( !scope_files.empty() );

  auto const sorted_files = sort( scope_files, sort_label_predicate ) ;
  auto const unique_files = unique( sorted_files, unique_label_predicate );
  
  auto out = vector< string >();
  
  for_each( unique_files, [&out]( const auto & file )
  {
    out.push_back( file.label );
  } ) ;

  return make_pair( unique_files, out );
}

} // namespace gMeasure
  
} // namespace gTBC
