//
//  periodic_time_distribution.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/construct/periodic_time_distribution.h"
#include "algorithm/algorithm.h"

namespace math {

namespace construct {

auto
periodic_time_distribution( units::quantity< units::si::frequency > const & frequency,
                            size_t const cycles,
                            size_t const count )
noexcept -> std::vector< units::quantity< units::si::time > >
{
  assert( cycles > 0 );
  assert( count > 0 );
  assert( frequency.value() > 0 );

  using namespace units;
  using algorithm::generate;
  
  using std::vector;
  using std::begin;
  using std::end;

  auto const period = quantity< dimensionless >( cycles  ) / frequency;
  auto const increment = period / quantity<dimensionless>(count - 1 );
  auto const starting_time = 0 * seconds ;
  
  auto time_distribution = vector< quantity< si::time > >( count, starting_time );
  
  auto scratch = quantity< si::time > ( starting_time ) ;
  const auto skip_first_step = begin( time_distribution ) + 1 ;
  
  generate( skip_first_step , end( time_distribution ), [&]() noexcept
  {
    scratch += increment;
    return scratch;
  } ) ;
  
  return time_distribution;
}

auto
periodic_time_distribution( units::quantity< units::si::frequency > const & frequency,
                            size_t const count )
noexcept -> std::vector< units::quantity< units::si::time > >
{
  assert( count > 0 );
  assert( frequency.value() > 0 );

  auto const cycles = size_t(1);
  auto const time_distribution = periodic_time_distribution( frequency, cycles, count);
  return time_distribution;
}
  
} // namespace construct
  
} // namespace math
