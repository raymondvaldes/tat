//
//  a_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <stdio.h>

#define BOOST_TEST_NO_LIB

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <cmath>
#include "thermal/model/tbc2009/dimensionless/a.h"


BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( tbc2009 )
BOOST_AUTO_TEST_SUITE( dimensionless )


BOOST_AUTO_TEST_CASE( a_test )
{
  using namespace units;
  using std::sqrt;
  
  auto const alpha_z =
  quantity<thermal_diffusivity>( 2.3  * square_millimeters / second );
  
  auto const alpha_z_coat=
  quantity<thermal_diffusivity>( 3.5 * square_millimeters/ second );
  
  using thermal::model::tbc2009::dimensionless::a;
  
  auto const eval = a( alpha_z , alpha_z_coat );
  auto const tol = 1e10-15;
  
  auto const temp = sqrt( alpha_z.value() / alpha_z_coat.value() );
  
  BOOST_CHECK_CLOSE_FRACTION(  temp , eval.value(), tol ) ;

}


BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
