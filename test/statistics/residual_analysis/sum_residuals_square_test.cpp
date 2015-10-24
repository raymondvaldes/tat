//
//  sum_residuals_square_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vector>

#include "statistics/signal_processing/sum_residuals_square.h"
#include "units.h"

using statistics::signal_processing::sum_residuals_square;
using std::vector;
using namespace units;

BOOST_AUTO_TEST_SUITE( statistics )
BOOST_AUTO_TEST_SUITE( signal_processing )
BOOST_AUTO_TEST_SUITE( residual_analysis )

BOOST_AUTO_TEST_CASE( sum_residual_square_test_1 )
{
  auto const os = vector< double >( { 1, 2 } );
  auto const ms = vector< double >( { 3, 4 } );

  auto const res = sum_residuals_square( os, ms );
  
  BOOST_CHECK_EQUAL( res, 8 );
}

BOOST_AUTO_TEST_CASE( sum_residual_squaredouble )
{
  auto const os = vector< double >( { 1.1, 1.2 } );
  auto const ms = vector< double >( { 2.1, 2.2 } );

  auto const res = sum_residuals_square( os, ms );
  
  BOOST_CHECK_CLOSE_FRACTION( res, 2.0, 1e-15 );
}

BOOST_AUTO_TEST_CASE( sum_residual_square_quantity )
{
  auto const o_1 = quantity<plane_angle>( 1.1 * radians );
  auto const o_2 = quantity<plane_angle>( 1.2 * radians );

  auto const m_1 = quantity<plane_angle>( 2.1 * radians );
  auto const m_2 = quantity<plane_angle>( 2.2 * radians );

  auto const os = vector< quantity< plane_angle > >( { o_1, o_2 } );
  auto const ms = vector< quantity< plane_angle > >( { m_1, m_2 } );

  auto const s = sum_residuals_square( os, ms );
  
  BOOST_CHECK_CLOSE_FRACTION( s.value(), 2.0, 1e-15 );
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
