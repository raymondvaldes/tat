//
//  is_scope_file.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "gTBC/gMeasure/is_scope_file.h"

#include "gTBC/gMeasure/read_scope_file.h"
#include "algorithm/string/split.h"

using algorithm::string::split;

namespace gTBC {

namespace gMeasure {

auto
is_scope_file
(
  filesystem::path const & path
)
noexcept -> bool
{
  auto const file = path.filename() ;
  
  auto const fileExtension = file.extension() ;
  
  auto const correct_extension = fileExtension == ".dat";

  auto const fileName = file.stem() ;
  
  auto const tokens = split( fileName.string(), "_" );

  auto const ith_token = tokens.size();
  
  auto const is_file = ith_token > 3 ;
  
  auto const valid_name = is_file && correct_extension;
  
  return valid_name;
}


} // namespace gMeasure
  
} // namespace gTBC
