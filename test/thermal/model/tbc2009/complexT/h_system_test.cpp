//
//  h_system_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 4/1/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//


#define BOOST_TEST_NO_LIB

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <cmath>
#include "thermal/model/tbc2009/complexT/h_system.h"
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"


BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( tbc2009 )
BOOST_AUTO_TEST_SUITE( complexT )


BOOST_AUTO_TEST_CASE( h_system_test_app )
{
  using std::sqrt;
  using thermal::model::tbc2009::complexT::h_system;
  using thermal::model::tbc2009::dimensionless::HeatingProperties;
  using thermal::model::tbc2009::dimensionless::ThermalProperties;
  
  using namespace units;
  auto const R0 = 0.2_nd ;
  auto const R1 = 0.9_nd ;
  auto const b = 0.5_nd ;
  auto const Lambda = 0.05_nd ;

  auto const hp = HeatingProperties( Lambda, R0, R1, b );
  
  auto const a_sub = 2.5_nd;
  auto const gamma = 3.7_nd;
  auto const tp = ThermalProperties( gamma, a_sub );

  auto const l = 0.25_nd;
  auto const z = 0.1_nd;
 
  auto const h = h_system( z, hp, tp, l);
  
  auto const nu = 0.1_nd;
  auto const h_eval = h( nu, z ) ;

  assert( h_eval.value().real() ==  0.044589869254403218 ) ;
  assert( h_eval.value().imag() == -0.079849430274766556 ) ;
}

BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
