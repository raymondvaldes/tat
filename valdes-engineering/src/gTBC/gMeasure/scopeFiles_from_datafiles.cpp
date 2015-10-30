//
//  scopeFiles_from_datafiles.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "gTBC/gMeasure/scopeFiles_from_datafiles.h"
#include "algorithm/algorithm.h"

namespace gTBC {

namespace gMeasure {

using std::vector;
using algorithm::for_each;

auto
scopeFiles_from_datafiles
(
  std::vector< filesystem::path > const & data_paths
)
noexcept -> std::vector< ScopeFile >
{
  auto scopeFiles = vector< ScopeFile >();

  for_each( data_paths , [&scopeFiles]( auto const & data_path ) noexcept
  {
    if( is_scope_file( data_path ) )
    {
      auto const scopeFile = read_scope_file( data_path );
      scopeFiles.push_back( scopeFile ) ;
    }
  } );

 return scopeFiles;
}


} // namespace gMeasure
  
} // namespace gTBC
