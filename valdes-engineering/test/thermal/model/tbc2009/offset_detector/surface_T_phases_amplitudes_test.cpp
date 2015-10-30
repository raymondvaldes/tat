//
//  surface_T_phases_amplitudes.cpp
//  tat-test
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <cmath>
#include "thermal/model/tbc2009/complexT/h_system.h"
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"
#include "thermal/model/tbc2009/complexT/phase_amplitude.h"

#include "thermal/model/tbc2009/complexT/offset_detector/average_surface_phase_amplitude.h"
#include "thermal/model/tbc2009/complexT/average_surface_phase_amplitude.h"

BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( tbc2009 )
BOOST_AUTO_TEST_SUITE( offset_detector )


BOOST_AUTO_TEST_CASE( phase_amplitude_test )
{
  using std::sqrt;
  using thermal::model::tbc2009::complexT::h_system;
  using thermal::model::tbc2009::dimensionless::HeatingProperties;
  using thermal::model::tbc2009::dimensionless::ThermalProperties;
  using thermal::model::tbc2009::complexT::phase_amplitude;

  using thermal::model::tbc2009::complexT::offset_detector::average_surface_phase_amplitude;
//  
//  using namespace units;
//  auto const R0 = 0.2_nd ;
//  auto const R1 = 0.9_nd ;
//  auto const b = 5._nd ;
//  auto const Lambda = 0.05_nd ;
//
//  auto const hp = HeatingProperties( Lambda, R0, R1, b );
//  
//  auto const a_sub = 2.5_nd;
//  auto const gamma = 3.7_nd;
//  auto const tp = ThermalProperties( gamma, a_sub );
//
//  auto const z = 0.1_nd;
//  auto const r = 0.2_nd;
//  auto const l = 0.25_nd;
  
//  auto const eval_0_centered =
//  thermal::model::tbc2009::complexT::average_surface_phase_amplitude( r, hp, tp , l ) ;
//
//  auto const eval_0_offset = average_surface_phase_amplitude( hp, tp, l, 1._nd, r );
//  
  // very interesting, the if there is 2d spreading due to a small beam diameter
  // then it is very likely that any offset of the detector and the laser
  // will lead to significant differences than a centered detector model!!
}

BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
