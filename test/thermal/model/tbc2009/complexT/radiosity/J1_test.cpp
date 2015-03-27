//
//  J1_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB

#include <iostream>

#include <boost/test/unit_test.hpp>

#include "thermal/model/tbc2009/complexT/radiosity/J1.h"


BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( tbc2009 )
BOOST_AUTO_TEST_SUITE( complexT )
BOOST_AUTO_TEST_SUITE( radiosity )


BOOST_AUTO_TEST_CASE( J1_test_run )
{
  using namespace units;
  using units::abs;
  using std::abs;
  
  auto const R0 = quantity<dimensionless>(.2);
  auto const R1 = quantity<dimensionless>(.8);
  auto const Lambda = quantity<dimensionless>(.1);
  
  using thermal::model::tbc2009::complexT::radiosity::J1;
  
  auto const J_eval = J1( R0, R1, Lambda );
  auto const tol = 1e-8;
  
  BOOST_VERIFY( abs( .832988917 - J_eval.value() ) < tol) ;
}


BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
