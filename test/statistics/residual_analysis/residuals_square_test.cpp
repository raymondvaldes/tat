//
//  residuals_square.cpp
//  tat-test
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

#include "units.h"
#include "statistics/signal_processing/residuals_square.h"

using statistics::signal_processing::residuals_square;
using namespace units;
using std::vector;

BOOST_AUTO_TEST_SUITE( statistics )
BOOST_AUTO_TEST_SUITE( signal_processing )
BOOST_AUTO_TEST_SUITE( residuals_analysis )

BOOST_AUTO_TEST_CASE( residuals_square_test_1 )
{
  auto const a = vector<int>( {2} ) ;
  auto const b = vector<int>( {3} ) ;

  auto const res = residuals_square( a, b );
  
  BOOST_CHECK_EQUAL( res[0], 1 );
}

BOOST_AUTO_TEST_CASE( residuals_square_double )
{
  auto const a = vector<double>( {2.2} ) ;
  auto const b = vector<double>( {3.3} ) ;

  auto const res_d = residuals_square( a, b );
  
  BOOST_CHECK_CLOSE_FRACTION( res_d[0], 1.21, 1e-15 );
}

BOOST_AUTO_TEST_CASE( residuals_square_quantity )
{
  auto const a = vector< quantity< plane_angle >>( {2.0*radians, 3.5*radians}) ;
  auto const b = vector< quantity< plane_angle >>( {1.0*radians, 4.2*radians}) ;
  
  auto const res = residuals_square( a, b );
  
  BOOST_CHECK_CLOSE_FRACTION( res[0].value(), 1.0, 1e-15 );
  BOOST_CHECK_CLOSE_FRACTION( res[1].value(), 0.49, 1e-15 );
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
