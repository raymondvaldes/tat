//
//  stdVector2ublasVector.cpp
//  tat-test
//
//  Created by Raymond Valdes on 9/11/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include "algorithm/vector/stdVector2ublasVector.h"

typedef const std::vector<double> vectorDouble;
typedef boost::numeric::ublas::vector<double> uVectorDouble;


uVectorDouble convertAndCheck( vectorDouble& input, const double Tol ) {

  const size_t N = input.size();
  using algorithm::vector::stdVector2ublasVector;

  uVectorDouble ublasOutput = stdVector2ublasVector( input ) ;
  for( size_t i = 0 ; i < N ;  ++i ) {
    BOOST_CHECK_CLOSE_FRACTION( ublasOutput[i], input[i], Tol ) ;
  }
  return stdVector2ublasVector( input );
}

BOOST_AUTO_TEST_SUITE( algorithm )

struct AccessVectors4Boost {
  vectorDouble foo =        { 4 , 2.5 , 2 , 0 } ;
  vectorDouble zeroVector = { 0 , 0   , 0 , 0 } ;
  
  const double tol = 1e-12 ;
};

BOOST_FIXTURE_TEST_SUITE( vector, AccessVectors4Boost )

BOOST_AUTO_TEST_CASE( convert_1 ) {
  convertAndCheck( foo, tol);
}

BOOST_AUTO_TEST_CASE( convert_2 ) {
  convertAndCheck( zeroVector, tol);
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()