//
//  Lambda.cpp
//  tat-test
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB

#include <iostream>

#include <boost/test/unit_test.hpp>

#include "thermal/model/tbc2009/dimensionless/Lambda.h"


BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( tbc2009 )
BOOST_AUTO_TEST_SUITE( dimensionless )


BOOST_AUTO_TEST_CASE( Lambda_test )
{
  using namespace units;

  auto const opticalPenetration =
  quantity<length>( 2.3 * micrometers  );
  
  auto const length_coating=
  quantity<length>( 3.5 * millimeters );
  
  using thermal::model::tbc2009::dimensionless::Lambda;
  
  auto const eval = Lambda( opticalPenetration , length_coating );
  auto const tol = 1e10-15;
  
  auto const temp =  opticalPenetration.value() / length_coating.value() ;
  
  BOOST_CHECK_CLOSE_FRACTION(  temp , eval.value(), tol ) ;
}

BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
