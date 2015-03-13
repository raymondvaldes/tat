//
//  get_pair_measurements_at_frequency.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>
#include <iostream>

#include "gTBC/gMeasure/get_pair_measurements_at_frequency.h"
#include "algorithm/algorithm.h"

namespace gTBC {
  
namespace gMeasure {

using std::abs;
using std::make_pair;
using algorithm::for_each;
using std::vector;

auto get_pair_measurements_at_frequency
(
  std::vector< Unique_scope_measurement > const & unique_measurements,
  units::quantity<units::si::frequency> const & frequency
) -> void
////noexcept -> std::pair<  thermal::equipment::detector::Measurements,
////                        thermal::equipment::detector::Measurements >
{

  auto temp = vector<Unique_scope_measurement>();
  
  for_each( unique_measurements, [&]( auto const & measurement )
  {
    const auto current_frequency =
    abs(measurement.laser_modulation_frequency.value() - frequency.value() ) < 1e-10 ;
    
    if( current_frequency )
    {
        temp.push_back( measurement );
    }
  
  } );

  

//  assert( temp.size() == 2 );
//  const auto output = make_pair( temp.front() , temp.back() );
//  return output;
}

  
} // gMeasure
  
} // gTBC
