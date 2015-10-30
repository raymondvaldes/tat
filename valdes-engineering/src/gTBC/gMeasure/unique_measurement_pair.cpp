//
//  unique_measurement_pair.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//


#include "gTBC/gMeasure/unique_measurement_pair.h"
#include "gTBC/gMeasure/get_pair_measurements_at_frequency.h"

#include "algorithm/algorithm.h"

namespace gTBC {

namespace gMeasure {

using algorithm::for_each;

auto unique_measurement_pairs
(
  std::vector< Unique_scope_measurement > const & unique_measurements,
  std::vector< units::quantity< units::si::frequency > > unique_frequencies
)
noexcept -> std::vector< std::pair< Unique_scope_measurement,
                                    Unique_scope_measurement > >
{
  auto output = std::vector< std::pair< Unique_scope_measurement,
                                        Unique_scope_measurement > >();

  for_each( unique_frequencies, [&]( auto const & freq ) noexcept
  {
    output.push_back(
    get_pair_measurements_at_frequency( unique_measurements, freq ) ) ;
  } );
  
  return output;
}
  
  
} // namespace gMeasure

} // namespace gTBC


