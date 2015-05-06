////
////  sum_residuals_square_test.cpp
////  tat-test
////
////  Created by Raymond Valdes on 5/6/15.
////  Copyright (c) 2015 Raymond Valdes. All rights reserved.
////
//
//#include <boost/test/unit_test.hpp>
//#include <boost/test/execution_monitor.hpp>
//#include <vector>
//
//#include "statistics/signal_processing/sum_residuals_square.h"
//#include "units.h"
//
////using statistics::signal_processing::sum_residuals_square;
//using std::vector;
//using namespace units;
//
//BOOST_AUTO_TEST_SUITE( statistics )
//BOOST_AUTO_TEST_SUITE( signal_processing )
//BOOST_AUTO_TEST_SUITE( residual_analysis )
//
////BOOST_AUTO_TEST_CASE( residual_square_test_1 )
////{
////  auto const a = 2;
////  auto const b = 3;
////
////  auto const res = residual_square( a, b );
////  
////  BOOST_CHECK_EQUAL( res, 1 );
////}
////
////BOOST_AUTO_TEST_CASE( residual_square_double )
////{
////  auto const a = 2.2;
////  auto const b = 3.3;
////
////  auto const res = residual_square( a, b );
////  
////  BOOST_CHECK_CLOSE_FRACTION( res, 1.21, 1e-15 );
////}
////
////BOOST_AUTO_TEST_CASE( sum_residual_square_quantity )
////{
////  auto const o_1 = quantity<plane_angle>( 1.1 * radians );
////  auto const o_2 = quantity<plane_angle>( 1.2 * radians );
////
////  auto const m_1 = quantity<plane_angle>( 2.1 * radians );
////  auto const m_2 = quantity<plane_angle>( 2.2 * radians );
////
////  auto const os = vector< quantity< plane_angle > >( { o_1, o_2 } );
////  auto const ms = vector< quantity< plane_angle > >( { m_1, m_2 } );
////
////  //sum_residuals_square( os, ms );
////  
//// // BOOST_CHECK_CLOSE_FRACTION( res.value(), 1.21, 1e-15 );
////}
//
//BOOST_AUTO_TEST_SUITE_END()
//BOOST_AUTO_TEST_SUITE_END()
//BOOST_AUTO_TEST_SUITE_END()