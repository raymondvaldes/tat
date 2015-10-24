//
//  temperature_TEST.cpp
//  tat-test
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <cmath>

#include "thermal/model/oneLayer2D/complex/temperature.h"

BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( oneLayer2D )
BOOST_AUTO_TEST_SUITE( complex )

using thermal::model::oneLayer2D::complex::temperature;
using namespace units;

BOOST_AUTO_TEST_CASE( complex_temperature_test )
{

  auto const z = 0.01_nd;
  auto const r = 0.01_nd;
  auto const b = 0.5_nd;
  auto const l = .2_nd;
  auto const dT = 1.0*kelvin;
  
  auto const t0 = temperature( 0.0_nd,  1.0_nd, b, l, dT);
  auto const t1 = temperature( 0.01_nd, 0.1_nd, b, l, dT);
  auto const t2 = temperature( 0.1_nd,  0.01_nd, b, l, dT);
  auto const t3 = temperature( 1.0_nd,  0.0_nd, b, l, dT);

//  using std::sqrt;
//  using thermal::model::tbc2009::complexT::h_system;
//  using thermal::model::tbc2009::dimensionless::HeatingProperties;
//  using thermal::model::tbc2009::dimensionless::ThermalProperties;
//  
//  using namespace units;
//  auto const R0 = 0.2_nd ;
//  auto const R1 = 0.9_nd ;
//  auto const b = 0.5_nd ;
//  auto const Lambda = 0.05_nd ;
//
//  auto const hp = HeatingProperties( Lambda, R0, R1, b );
//  
//  auto const a_sub = 2.5_nd;
//  auto const gamma = 3.7_nd;
//  auto const tp = ThermalProperties( gamma, a_sub );
//
//  auto const l = 0.25_nd;
//  auto const z = 0.1_nd;
// 
//  auto const h = h_system( z, hp, tp, l);
//  
//  auto const nu = 0.1_nd;
//  auto const h_eval = h( nu, z ) ;
//
//  assert( h_eval.value().real() ==  0.044589869254403218 ) ;
//  assert( h_eval.value().imag() == -0.079849430274766556 ) ;
}

BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite