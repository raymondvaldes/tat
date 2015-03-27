//
//  b.cpp
//  tat-test
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB

#include <iostream>

#include <boost/test/unit_test.hpp>

#include "thermal/model/tbc2009/dimensionless/b.h"


BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( tbc2009 )
BOOST_AUTO_TEST_SUITE( dimensionless )


BOOST_AUTO_TEST_CASE( b_test )
{
  using namespace units;
  
  auto const radius =
  quantity<length>( 2.3 * millimeters  );
  
  auto const length_coating=
  quantity<length>( 3.5 * millimeters );
  
  using thermal::model::tbc2009::dimensionless::b;
  
  auto const eval = b( radius , length_coating );
  auto const tol = 1e10-15;
  
  auto const temp =  radius.value() / length_coating.value() ;
  
  BOOST_CHECK_CLOSE_FRACTION(  temp , eval.value(), tol ) ;
}



BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
