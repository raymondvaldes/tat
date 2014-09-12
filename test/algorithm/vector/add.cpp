//
//  add.cpp
//  tat-test
//
//  Created by Raymond Valdes on 9/11/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "algorithm/vector/add.h"
typedef const std::vector<double> vectorDouble;
using algorithm::vector::add;

BOOST_AUTO_TEST_SUITE( algorithm )

struct AccessVectors {
  vectorDouble foo =        { 4 , 2.5 , 2 , 0 } ;
  vectorDouble bar =        { 0 , 1   , 2 , 3 } ;
  vectorDouble fooPLUSbar = { 4 , 3.5 , 4 , 3 } ;
  vectorDouble foofoo =     { 8 , 5   , 4 , 0 } ;
  vectorDouble zeroVector = {0,0,0,0};
  
  const double tol = 1e-12 ;
};

BOOST_FIXTURE_TEST_SUITE( vector, AccessVectors )

BOOST_AUTO_TEST_CASE( add_0 ) {
  vectorDouble out = add( zeroVector, zeroVector ) ;
  
  const size_t N = zeroVector.size();
  for( size_t i = 0; i < N ; ++i )
    BOOST_CHECK_CLOSE_FRACTION( zeroVector[i], zeroVector[i], tol ) ;
}

BOOST_AUTO_TEST_CASE( add_1 ) {
  vectorDouble out = add( foo, bar ) ;
  
  const size_t N = foo.size();
  for( size_t i = 0; i < N ; ++i )
    BOOST_CHECK_CLOSE_FRACTION( out[i], fooPLUSbar[i], tol ) ;
}

BOOST_AUTO_TEST_CASE( add_itself ) {
  vectorDouble out = add( foo, foo ) ;
  
  const size_t N = foo.size();
  for( size_t i = 0; i < N ; ++i )
    BOOST_CHECK_CLOSE_FRACTION( out[i], foofoo[i], tol ) ;
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()