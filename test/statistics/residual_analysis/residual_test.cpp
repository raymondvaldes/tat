//
//  residual_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "statistics/signal_processing/residuals/residual.h"
#include "units.h"

using statistics::signal_processing::residual;
using namespace units;

BOOST_AUTO_TEST_SUITE( statistics )
BOOST_AUTO_TEST_SUITE( signal_processing )
BOOST_AUTO_TEST_SUITE( residual_analysis )

BOOST_AUTO_TEST_CASE( residual_test_1 )
{
  auto const a = 2;
  auto const b = 3;

  auto const res = residual( a, b );
  
  BOOST_CHECK_EQUAL( res, -1 );
}

BOOST_AUTO_TEST_CASE( residual_test_double )
{
  auto const a = 2.2;
  auto const b = 3.3;

  auto const res = residual( a, b );
  
  BOOST_CHECK_CLOSE_FRACTION( res, -1.1, 1e-15 );
}

BOOST_AUTO_TEST_CASE( residual_test_quantity )
{
  auto const a = quantity<plane_angle>( 2.2 * radians );
  auto const b = quantity<plane_angle>( 3.3 * radians );

  auto const res = residual( a, b );
  
  BOOST_CHECK_CLOSE_FRACTION( res.value(), -1.1, 1e-15 );
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()