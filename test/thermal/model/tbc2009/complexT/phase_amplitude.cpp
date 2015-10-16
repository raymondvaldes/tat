//
//  phase_amplitude.cpp
//  tat-test
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//


#define BOOST_TEST_NO_LIB

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <cmath>
#include "thermal/model/tbc2009/complexT/h_system.h"
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"
#include "thermal/model/tbc2009/complexT/phase_amplitude.h"


BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( tbc2009 )
BOOST_AUTO_TEST_SUITE( complexT )


BOOST_AUTO_TEST_CASE( phase_amplitude_test )
{
  using std::sqrt;
  using thermal::model::tbc2009::complexT::h_system;
  using thermal::model::tbc2009::dimensionless::HeatingProperties;
  using thermal::model::tbc2009::dimensionless::ThermalProperties;
  using thermal::model::tbc2009::complexT::phase_amplitude;
  
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
  auto const r = 0.2_nd;
  
//  auto const eval_0 = phase_amplitude( z, 1.0_nd, hp, tp, l ) ;
//  auto const eval_1 = phase_amplitude( z, 2.2_nd, hp, tp, l ) ;
//  auto const eval_2 = phase_amplitude( z, 3.4_nd, hp, tp, l ) ;
//  auto const eval_3 = phase_amplitude( z, 4.6_nd, hp, tp, l ) ;
//
////  assert( eval_0.first.value() ==  0 ) ;
//  assert( eval_1.first.value() ==  0 ) ;
//  assert( eval_2.first.value() ==  0 ) ;
//  assert( eval_3.first.value() ==  0 ) ;
  
}

BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
