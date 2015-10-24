//
//  si_literals.cpp
//  tat-test
//
//  Created by Raymond Valdes on 4/1/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//


#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "units/si/si_literals.h"

BOOST_AUTO_TEST_SUITE( units )
BOOST_AUTO_TEST_SUITE( si_test )

BOOST_AUTO_TEST_CASE( si_literals_test )
{
  using namespace units;
  auto const x = 0.5_nd ;
  auto const y = quantity<dimensionless>( 0.5 );
  
  assert( x == y );

}



BOOST_AUTO_TEST_SUITE_END()  // suite si
BOOST_AUTO_TEST_SUITE_END()  // suite units
