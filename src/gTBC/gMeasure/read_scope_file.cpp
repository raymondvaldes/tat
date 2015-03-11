//
//  read_scope_file.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include <string>

#include "gTBC/gMeasure/read_scope_file.h"
#include "algorithm/string/split.h"
#include "gTBC/gMeasure/is_scope_file.h"

namespace gTBC {

namespace gMeasure {

using algorithm::string::split;
using units::quantity;
using units::si::frequency;
using units::si::wavelength;
using units::si::micrometers;
using units::si::hertz;

auto
read_scope_file
(
  filesystem::path const & path
)
noexcept -> ScopeFile
{
  assert( is_scope_file( path ) );

  auto const file = path.filename();
  auto const fileName = file.stem() ;

  auto const melissa = "_";

  auto const tokens = split( fileName.string(), melissa );

  auto ith_token = tokens.size();
  
  ith_token--;
  
  auto const id_number = stoul( tokens[ ith_token ] ) ;
  ith_token--;
  
  auto const modulation_frequency = quantity< frequency >( stod( tokens[ith_token] ) * hertz );
  ith_token--;
  
  auto const lambda = quantity< wavelength >( stod( tokens[ith_token] ) * micrometers ) ;

  auto label = tokens.front();
  for( auto i = 1u ; i < ith_token ; i++ )
    label += "_" + tokens[i];

  auto const scopeFile = ScopeFile( label, lambda, modulation_frequency, id_number, path ) ;
  return scopeFile;
}

} // namespace gMeasure
  
} // namespace gTBC
