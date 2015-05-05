//
//  planks_law_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB

#include <iostream>

#include <boost/test/unit_test.hpp>

#include "thermal/emission/planks_law/planks_law.h"

using thermal::emission::monochromatic_blackbody_emissive_power::planks_law;
using namespace units;

BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( emission )
BOOST_AUTO_TEST_SUITE( monochromatic_blackbody_emissive_power )

BOOST_AUTO_TEST_CASE( planks_law_case_1 )
{
  auto const T = quantity< si::temperature >( 1400.0 * kelvin );
  auto const lambda = quantity< length >( 2.07e-6 * meters ) ;
  
  auto const E_1 = planks_law( T , lambda );
  BOOST_CHECK_CLOSE_FRACTION( E_1.value(),  6.92e10 , 1e-3 );
  
}

BOOST_AUTO_TEST_CASE( planks_law_case_2 )
{
  auto const T = quantity< si::temperature >( 1400.0 * kelvin );
  auto const lambda = quantity< length >( 5.0e-6 * meters ) ;
  
  auto const E_1 = planks_law( T , lambda );
  BOOST_CHECK_CLOSE_FRACTION( E_1.value(),  1.758e10 , 1e-3 );
  
}

BOOST_AUTO_TEST_SUITE_END()  // suite monochromatic_blackbody_emissive_power
BOOST_AUTO_TEST_SUITE_END()  // suite emission
BOOST_AUTO_TEST_SUITE_END()  // suite thermal
