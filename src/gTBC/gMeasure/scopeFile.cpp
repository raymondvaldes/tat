//
//  scopeFile.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>

#include "gTBC/gMeasure/scopeFile.h"

namespace gTBC {

namespace gMeasure {

ScopeFile::ScopeFile
(
  std::string const & label_,
  units::quantity< units::si::wavelength > const & monochorometer_lambda_,
  units::quantity< units::si::frequency > const & laser_modulation_frequency_,
  size_t const & id_number_,
  filesystem::path const & path_
)
: label( label_ ),
  monochorometer_lambda( monochorometer_lambda_ ),
  laser_modulation_frequency( laser_modulation_frequency_ ),
  id_number( id_number_ ),
  path( path_ )
{
  assert( laser_modulation_frequency_.value() > 0 ) ;
  assert( monochorometer_lambda_.value() > 0 ) ;
  assert( !label_.empty() ) ;
  assert( path_.has_filename() ) ;
  assert( path.has_extension() ) ;
}
  
} // namespace gMeasure
  
} // namespace gTBC
