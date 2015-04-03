//
//  points_of_intersection.cpp
//  tat-test
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

#include "math/geometry/intersect/two_circles/points_of_intersection.h"
using math::geometry::intersect::two_circles::points_of_intersection;

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( geometry )
BOOST_AUTO_TEST_SUITE( intersect )
BOOST_AUTO_TEST_SUITE( two_circles )

using namespace units;

BOOST_AUTO_TEST_CASE( points_test_1 ) {
  
  auto const r =  quantity< length >( .3 * meters );
  auto const offset = quantity< length >( .2 * meters ) ;
  auto const radius =  quantity< length >( .3 * meters );
  
  auto const points = points_of_intersection( r, offset, radius );

  auto const tol = 1e-5;
  BOOST_CHECK_CLOSE_FRACTION( points.first.x.value() , 0.1 , tol) ;
  BOOST_CHECK_CLOSE_FRACTION( points.first.y.value() , -0.282843, tol ) ;
  
  BOOST_CHECK_CLOSE_FRACTION( points.second.x.value() , 0.1 , tol) ;
  BOOST_CHECK_CLOSE_FRACTION( points.second.y.value() , 0.282843, tol ) ;
}

BOOST_AUTO_TEST_SUITE_END() // two_circles
BOOST_AUTO_TEST_SUITE_END() // intersect
BOOST_AUTO_TEST_SUITE_END() // geometry
BOOST_AUTO_TEST_SUITE_END() // math
