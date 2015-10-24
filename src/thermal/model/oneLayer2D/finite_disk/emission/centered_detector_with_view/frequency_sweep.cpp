//
//  frequency_sweep.cpp
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "frequency_sweep.hpp"
#include "measurement.hpp"
#include <cassert>
#include <iterator>
#include "algorithm/algorithm.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace disk{
namespace emission{
namespace centered_detector_with_view{

using thermal::model::complex::Temperature;
using thermal::model::complex::Temperatures;
using algorithm::transform;
using std::vector;
using std::begin;

auto
frequency_sweep
(
  slab::Slab const & slab,
  Optics const & optics,
  equipment::laser::Modulation_frequencies const & frequencies
)
noexcept -> thermal::model::complex::Temperatures
{
  assert( !frequencies.empty() );
  auto const size = frequencies.size();
  
  auto temperatures = vector< Temperature>( size );
  
  transform( frequencies, begin(temperatures), [&slab, &optics]
  ( auto const f ) noexcept
  {
    auto const t = measurement( slab, optics, f );
    return t;
  } );
  
  auto const out = Temperatures( temperatures );

  return out;
}

} // 
} // dimensionless
} // disk
} // finite_disk
} // oneLayer2d
} // model
} // thermal
