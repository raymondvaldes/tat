//
//  periodic_time_distribution.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/construct/periodic_time_distribution.h"
#include "assert/assertExtensions.h"
#include "algorithm/algorithm.h"

namespace math {

namespace construct {

auto
periodic_time_distribution( units::quantity< units::si::frequency > const & frequency,
                            size_t const cycles,
                            size_t const count )
noexcept -> std::vector< units::quantity< units::si::time > >
{
  assert_gt_zero( cycles ) ;
  assert_gt_zero( count ) ;
  assert_gt_zero( frequency ) ;

  using units::quantity;
  using units::si::dimensionless;
  using units::si::time;
  using units::si::seconds;
  using algorithm::generate;
  
  using std::vector;
  using std::begin;
  using std::end;

  auto const period = quantity< dimensionless >( cycles  ) / frequency;
  auto const increment = period / quantity<dimensionless>(count - 1 );
  auto const starting_time = 0 * seconds ;
  
  auto time_distribution = vector< quantity< time > >( count, starting_time );
  
  auto scratch = quantity< time > ( starting_time ) ;
  const auto skip_first_step = begin( time_distribution ) + 1 ;
  
  generate( skip_first_step , end( time_distribution ), [&]() noexcept
  {
    scratch += increment;
    return scratch;
  } ) ;
  
  return time_distribution;
}

  
} // namespace construct
  
} // namespace math
