//
//  temperatures_factory_dummy_amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "temperatures_factory_dummy_amplitudes.hpp"
#include "algorithm/algorithm.h"
#include "amplitude.h"
#include <vector>
#include <gsl.h>

namespace thermal{
namespace model{
namespace complex{

using algorithm::transform;
using std::vector;
using namespace units;

auto
temperature_factory_dummy_amplitudes( Phases const & phases )
noexcept -> Temperatures
{
  Expects( !phases.empty() );

  auto const size = phases.size();
  auto temperatures = vector< Temperature > ( size );
  
  
  
  transform( phases, temperatures.begin(), []
  ( auto const p ) noexcept
  {
      auto const dummey = Amplitude(1.0 * si::kelvin );
      return Temperature( p, dummey );
  } );

  auto const Ts = Temperatures( temperatures );
  
  Ensures( !Ts.empty() );
  Ensures( Ts.size() == size );
  return Ts;
}

} // namespace complex
} // namespace model
} // namespace thermal
