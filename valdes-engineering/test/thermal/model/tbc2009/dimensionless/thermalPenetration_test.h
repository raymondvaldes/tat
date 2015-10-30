//
//  thermalPenetration_test.h
//  tat-test
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_test__thermalPenetration_test__
#define __tat_test__thermalPenetration_test__

#define BOOST_TEST_NO_LIB

#include <iostream>
#include <cmath>

#include <boost/test/unit_test.hpp>

#include "thermal/model/tbc2009/dimensionless/thermal_penetration.h"


BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( tbc2009 )
BOOST_AUTO_TEST_SUITE( dimensionless )


BOOST_AUTO_TEST_CASE( thermal_penetration_test )
{
  using namespace units;
  using std::sqrt;
  using std::abs;

  auto const alpha =
  quantity< thermal_diffusivity >( 23. * square_millimeters / second );

  auto const length_coating=
  quantity<length>( 3320. * millimeters );
  
  auto const f = quantity< frequency >( 2.0 * hertz);
  
  auto const eval =
  thermal::model::tbc2009::dimensionless::thermal_penetration(
    f, length_coating, alpha );
  
  auto const tol = 1e10-15;
  
  auto const temp =
  sqrt( alpha.value() / ( 2.*M_PI* f.value()) ) / length_coating.value() ;
  
  BOOST_CHECK_CLOSE_FRACTION(  temp , eval.value(), tol ) ;
}

BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids

#endif /* defined(__tat_test__thermalPenetration_test__) */
