//
//  subtract.cpp
//  tat-test
//
//  Created by Raymond Valdes on 9/11/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "algorithm/vector/subtract.h"
typedef const std::vector<double> vectorDouble;
using algorithm::vector::subtract;

BOOST_AUTO_TEST_SUITE( algorithm )

struct subtractVectors {
  vectorDouble foo =          { 4 , 2.5 , 2 , 0 } ;
  vectorDouble bar =          { 0 , 1   , 2 , 3 } ;
  vectorDouble fooMINUSbar =  { 4 , 1.5 , 0 , -3 } ;

  vectorDouble zeroVector = {0,0,0,0};
  
  const double tol = 1e-12;
};

BOOST_FIXTURE_TEST_SUITE( vector, subtractVectors )


BOOST_AUTO_TEST_CASE( subtract_0 ) {
  vectorDouble out = subtract( zeroVector, zeroVector ) ;
  
  const size_t N = foo.size();
  for( size_t i = 0; i < N ; ++i )
    BOOST_CHECK_CLOSE_FRACTION( zeroVector[i], zeroVector[i], tol ) ;

}

BOOST_AUTO_TEST_CASE( subtract_1 ) {
  vectorDouble out = subtract( foo, bar ) ;
  
  const size_t N = foo.size();
  for( size_t i = 0; i < N ; ++i )
    BOOST_CHECK_CLOSE_FRACTION( out[i], fooMINUSbar[i], tol ) ;
    
}

BOOST_AUTO_TEST_CASE( subtract_itself ) {
  vectorDouble out = subtract( foo, foo ) ;
  
  const size_t N = foo.size();
  for( size_t i = 0; i < N ; ++i )
    BOOST_CHECK_CLOSE_FRACTION( out[i], zeroVector[i], tol ) ;

}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()