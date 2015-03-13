//
//  Unique_scope_measurements.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "gTBC/gMeasure/Unique_scope_measurement.h"
#include "algorithm/algorithm.h"

namespace gTBC {

namespace gMeasure {

using algorithm::for_each;

Unique_scope_measurement::Unique_scope_measurement
(
  std::vector< ScopeFile > scopeFiles_
)
: scopeFiles( scopeFiles_) ,
  label( scopeFiles_.front().label ),
  monochorometer_lambda( scopeFiles_.front().monochorometer_lambda ),
  laser_modulation_frequency( scopeFiles_.front().laser_modulation_frequency ),
  size( scopeFiles_.size() ),
  cycles( 6 )
{
  assert( laser_modulation_frequency.value() > 0 ) ;
  assert( monochorometer_lambda.value() > 0 ) ;
  assert( !label.empty() ) ;
}



} // namespace gMeasure

} // namespace gTBC
