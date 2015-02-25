//
//  ifzero.cpp
//  tat-test
//
//  Created by Raymond Valdes on 9/12/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//


#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include "algorithm/vector/ifzero.h"

using algorithm::vector::ifzero;
typedef const std::vector<double> vectorDouble;


BOOST_AUTO_TEST_SUITE( algorithm )

struct AccessVectors4ifZero {
  vectorDouble foo =        { 4 , 2.5 , 2 , 1 } ;
  vectorDouble bar =        { 4 , 2.5 , -1 , 0 } ;
  vectorDouble zeroVector = { 0 , 0   , 0 , 0 } ;
  
  const double tol = 1e-14 ;
};

BOOST_FIXTURE_TEST_SUITE( vector, AccessVectors4ifZero )

BOOST_AUTO_TEST_CASE( check_zero_vector_1 ) {
  BOOST_CHECK( ifzero( zeroVector ) ) ;
}

BOOST_AUTO_TEST_CASE( check_zero_vector_2 ) {
  BOOST_CHECK( ifzero( zeroVector.data(), zeroVector.size() ) ) ;
}

BOOST_AUTO_TEST_CASE( check_zero_vector_3 ) {
  BOOST_CHECK( !if_not_zero( zeroVector ) ) ;
}

BOOST_AUTO_TEST_CASE( check_zero_vector_4 ) {
  BOOST_CHECK( !if_not_zero( zeroVector.data(), zeroVector.size() ) ) ;
}

/////////////

BOOST_AUTO_TEST_CASE( foo_1 ) {
  BOOST_CHECK( !ifzero( foo ) ) ;
}

BOOST_AUTO_TEST_CASE( foo_2 ) {
  BOOST_CHECK( !ifzero( foo.data(), foo.size() ) ) ;
}

BOOST_AUTO_TEST_CASE( foo_3 ) {
  BOOST_CHECK( if_not_zero( foo ) ) ;
}

BOOST_AUTO_TEST_CASE( foo_4 ) {
  BOOST_CHECK( if_not_zero( foo.data(), foo.size() ) ) ;
}

/////////////

BOOST_AUTO_TEST_CASE( bar_1 ) {
  BOOST_CHECK( ifzero( bar ) ) ;
}

BOOST_AUTO_TEST_CASE( bar_2 ) {
  BOOST_CHECK( ifzero( bar.data(), bar.size() ) ) ;
}

BOOST_AUTO_TEST_CASE( bar_3 ) {
  BOOST_CHECK( !if_not_zero( bar ) ) ;
}

BOOST_AUTO_TEST_CASE( bar_4 ) {
  BOOST_CHECK( !if_not_zero( bar.data(), bar.size() ) ) ;
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()