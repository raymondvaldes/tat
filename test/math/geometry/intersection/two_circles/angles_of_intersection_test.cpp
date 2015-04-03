//
//  angles_of_intersection_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

#include "math/geometry/intersect/two_circles/angles_of_intersection.h"
using math::geometry::intersect::two_circles::angles_of_intersection;

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( geometry )
BOOST_AUTO_TEST_SUITE( intersect )
BOOST_AUTO_TEST_SUITE( two_circles )

using namespace units;

BOOST_AUTO_TEST_CASE( angles_test_1 ) {
  
  auto const r =  quantity< length >( 1.1 * millimeters );
  auto const offset = quantity< length >( 1.0 * millimeters ) ;
  auto const radius =  quantity< length >( 1.0 * millimeters );
  
  auto const angles = angles_of_intersection( r, offset, radius );

  auto const tol = 1e-5;
  BOOST_CHECK_CLOSE_FRACTION( angles.first.value(), -0.988432 , tol) ;
  BOOST_CHECK_CLOSE_FRACTION( angles.second.value(),  0.988432, tol ) ;
  
}

BOOST_AUTO_TEST_CASE( angles_test_2 ) {
  
  auto const r =  quantity< length >( 0.001 * millimeters );
  auto const offset = quantity< length >( 1.0 * millimeters ) ;
  auto const radius =  quantity< length >( 1.0 * millimeters );
  
  auto const angles = angles_of_intersection( r, offset, radius );

  auto const tol = 1e-5;
  BOOST_CHECK_CLOSE_FRACTION( angles.first.value(), -1.5703 , tol) ;
  BOOST_CHECK_CLOSE_FRACTION( angles.second.value(),  1.5703, tol ) ;
}

BOOST_AUTO_TEST_CASE( angles_test_3 ) {
  
  auto const r =  quantity< length >( 1.0 * millimeters );
  auto const offset = quantity< length >( 1.0 * millimeters ) ;
  auto const radius =  quantity< length >( 1.0 * millimeters );
  
  auto const angles = angles_of_intersection( r, offset, radius );

  auto const tol = 1e-5;
  BOOST_CHECK_CLOSE_FRACTION( angles.first.value(), -1.0472 , tol) ;
  BOOST_CHECK_CLOSE_FRACTION( angles.second.value(), 1.0472, tol ) ;
}

BOOST_AUTO_TEST_CASE( angles_test_4 ) {
  
  auto const r =  quantity< length >( 0.5 * millimeters );
  auto const offset = quantity< length >( 0.7 * millimeters ) ;
  auto const radius =  quantity< length >( 1.0 * millimeters );
  
  auto const angles = angles_of_intersection( r, offset, radius );

  auto const tol = 1e-5;
  BOOST_CHECK_CLOSE_FRACTION( angles.first.value(), -1.951343518484716 , tol) ;
  BOOST_CHECK_CLOSE_FRACTION( angles.second.value(), 1.951343518484716, tol ) ;
}

BOOST_AUTO_TEST_CASE( angles_test_5 ) {
  
  auto const r =  quantity< length >( .2 * millimeters );
  auto const offset = quantity< length >( 0.2 * millimeters ) ;
  auto const radius =  quantity< length >( 0.3 * millimeters );
  
  auto const angles = angles_of_intersection( r, offset, radius );

  auto const tol = 1e-5;
  BOOST_CHECK_CLOSE_FRACTION( angles.first.value(), -1.6961241579629616 , tol) ;
  BOOST_CHECK_CLOSE_FRACTION( angles.second.value(), 1.6961241579629616, tol ) ;
}

BOOST_AUTO_TEST_SUITE_END() // two_circles
BOOST_AUTO_TEST_SUITE_END() // intersect
BOOST_AUTO_TEST_SUITE_END() // geometry
BOOST_AUTO_TEST_SUITE_END() // math
