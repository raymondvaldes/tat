//
//  sample_variance_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "statistics/signal_processing/variance/sample_variance.h"

using std::vector;
using namespace units;
using statistics::signal_processing::sample_variance;

BOOST_AUTO_TEST_SUITE( statistics )
BOOST_AUTO_TEST_SUITE( signal_processing )
BOOST_AUTO_TEST_SUITE( variance )

BOOST_AUTO_TEST_CASE( sample_variance_test_double )
{
  auto const o_1 = 1.1;
  auto const o_2 = 1.2;

  auto const m_1 = 2.0;
  auto const m_2 = 2.2;

  auto const os = vector< double >( { o_1, o_2 } );
  auto const ms = vector< double >( { m_1, m_2 } );

  auto const s = sample_variance( os, ms );
  
  BOOST_CHECK_CLOSE_FRACTION( s, 0.905, 1e-15 );
}

BOOST_AUTO_TEST_CASE( sample_variance_test_1 )
{
  auto const o_1 = quantity<plane_angle>( 1.1 * radians );
  auto const o_2 = quantity<plane_angle>( 1.2 * radians );

  auto const m_1 = quantity<plane_angle>( 2.0 * radians );
  auto const m_2 = quantity<plane_angle>( 2.2 * radians );

  auto const os = vector< quantity< plane_angle > >( { o_1, o_2 } );
  auto const ms = vector< quantity< plane_angle > >( { m_1, m_2 } );

  auto const s = sample_variance( os, ms );
  
  BOOST_CHECK_CLOSE_FRACTION( s.value(), 0.905, 1e-15 );
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
