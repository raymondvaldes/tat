//
//  interval.cpp
//  tat-test
//
//  Created by Raymond Valdes on 6/27/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

#include <utility>
#include "math/geometry/interval.h"
#include "math/utility.hpp"

using math::Interval;
using std::vector;
using std::pair;
using std::make_pair;
typedef pair<double, double> pairDD;

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( test )


struct AccessIntervals {
  const pairDD myPair = pairDD( .01, 10 ) ;
  const Interval myInterval = Interval( myPair ) ;
  const size_t gridPoints = 18 ;

  const double tol  = 1e-14;
} ;

BOOST_FIXTURE_TEST_SUITE( interval, AccessIntervals)

BOOST_AUTO_TEST_CASE( constructor_test ) {
  
  const pairDD validPair( .01, 10 ) ;
  const pair<double, int> invalidPair = make_pair( .01, 10 ) ;
  const pair<int, int> intPair = make_pair( 0, 10 ) ;

  BOOST_CHECK_NO_THROW( Interval myInterval( validPair ) ) ;
  BOOST_CHECK_NO_THROW( Interval myInvalidPair( invalidPair ) ) ;
  BOOST_CHECK_NO_THROW( Interval myIntPair( intPair ) ) ;
}

BOOST_AUTO_TEST_CASE( get_left_end ) {
  const double left_end = myInterval.get_left_end();
  BOOST_CHECK_CLOSE( left_end, myPair.first, tol );
}

BOOST_AUTO_TEST_CASE( get_right_end ) {
  const double right_end = myInterval.get_right_end();
  BOOST_CHECK_CLOSE( right_end, myPair.second, tol );
}

BOOST_AUTO_TEST_CASE( is_invalid ) {

  const pairDD invalidPair = pairDD( 10,.01 ) ;
  const Interval myInvalidInterval = Interval( invalidPair ) ;
  const bool pass = myInvalidInterval.is_invalid() ;
  
  BOOST_CHECK( pass ) ;
}

BOOST_AUTO_TEST_CASE( is_valid ) {
  BOOST_CHECK( myInterval.is_valid() ) ;
}

BOOST_AUTO_TEST_CASE( set_ends ) {

  const pairDD newEndpoints = pairDD( .25, .7 ) ;
  Interval mutableInt = myInterval ;
  mutableInt.set_ends( newEndpoints ) ;
  
  BOOST_CHECK_CLOSE( mutableInt.get_left_end(), newEndpoints.first, tol ) ;
  BOOST_CHECK_CLOSE( mutableInt.get_right_end(), newEndpoints.second, tol ) ;
}

BOOST_AUTO_TEST_CASE( numberofOddIntervals ) {
  const size_t subspacing = myInterval.numberofOddIntervals( gridPoints ) ;
  
  const bool isOdd = ( subspacing % 2 == 1 ) ;
  
  BOOST_CHECK( isOdd ) ;
  
}

BOOST_AUTO_TEST_CASE( gridInterval ) {
  const size_t subspacing = myInterval.numberofOddIntervals( gridPoints ) ;

  typedef const vector< pair< double, double > > BoundPairs ;
  BoundPairs boundPairs = myInterval.gridInterval( subspacing ) ;
  
  BOOST_CHECK_CLOSE( boundPairs.front().first , myInterval.get_left_end(), tol);
  BOOST_CHECK_CLOSE( boundPairs.front().second, myInterval.get_left_end(), tol);

  BOOST_CHECK_CLOSE( boundPairs.back().first , myInterval.get_right_end(), tol);
  BOOST_CHECK_CLOSE( boundPairs.back().second, myInterval.get_right_end(), tol);
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()