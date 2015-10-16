//
//  periodic_time_distribution.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/5/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>
#include "units.h"
#include "math/construct/periodic_time_distribution.h"
#include "cout/vector/print.h"

using namespace units;
using math::construct::periodic_time_distribution;

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( construct )

BOOST_AUTO_TEST_CASE( periodic_time_distribution_one )
{
  auto const freq = 1.0 * hertz;
  auto const cycles = 2;
  auto const count = 10;

  auto const times = periodic_time_distribution( freq , cycles, count );

  //cout::vector::print( times );
  
}

BOOST_AUTO_TEST_CASE( periodic_time_distribution_two )
{
  auto const freq = 1.0 * hertz;
  auto const cycles = 1;
  auto const count = 10;

  auto const times = periodic_time_distribution( freq , count );

  //cout::vector::print( times );
  
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
