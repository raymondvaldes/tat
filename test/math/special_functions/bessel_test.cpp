//
//  bessel_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//


#include <cmath>

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

#include "math/special_functions/bessel.h"
#include "units.h"

using namespace units;
using std::abs;
using math::special_functions::bessel_j;

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( special_functions )

BOOST_AUTO_TEST_CASE( bessel_test_case )
{
  size_t const v1 = 0;
  
  auto const x1 = double( 2.3123 );
  auto const x2 = quantity<dimensionless>( x1 );
  
  auto const r0 = bessel_j( 0, x2 ) ;
  auto const r1 = bessel_j( 1, x2 ) ;
  auto const r2 = bessel_j( 2, x2 ) ;
  
  //calculated using wolfram alpha (
  auto const r0_wa =
  quantity<dimensionless>(0.0489130183781769214723562729626210818047575292740605);

  auto const r1_wa =
  quantity<dimensionless>(0.5376413580131548298653732412135844073835890659703832);
  
  auto const r2_wa =
  quantity<dimensionless>(0.4161143206463050487437690059489253502184133966182399);
  
  BOOST_CHECK_CLOSE( r0_wa.value(), r0.value(), 1e-13);
  BOOST_CHECK_CLOSE( r1_wa.value(), r1.value(), 1e-13);
  BOOST_CHECK_CLOSE( r2_wa.value(), r2.value(), 1e-13);
  

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
