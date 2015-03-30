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
  size_t const v1 = 1;
  size_t const v2 = 2;
  
  auto const x1 = double(2.3);
  auto const x2 = quantity<dimensionless>( x1 );
  
 // auto const r1 = bessel_j( v1, x1 ) ;
  auto const r2 = bessel_j( v2, x2 ) ;
  
//  auto const r1_wa = double(0.539873);
  auto const r2_wa = quantity<dimensionless>(.418076);
  
 // BOOST_CHECK_CLOSE( r1_wa, r1, 1e-4);
  BOOST_CHECK_CLOSE( r2_wa.value(), r2.value(), 1e10-10);
  

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
