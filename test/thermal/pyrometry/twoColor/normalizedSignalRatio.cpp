//
//  normalizedSignalRatio.cpp
//  tat-test
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include <iostream>

#include "units.h"
#include "thermal/pyrometry/twoColor/normalizedSignalRatio.h"
#include "thermal/pyrometry/twoColor/signalRatio.h"
#include "thermal/pyrometry/twoColor/calibratedSignalRatio.h"

BOOST_AUTO_TEST_SUITE( thermal )

BOOST_AUTO_TEST_SUITE( pyrometry )

BOOST_AUTO_TEST_SUITE( twoColor )


using units::quantity;
using units::si::length;
using units::si::micro;
using units::si::meters;
using units::si::dimensionless;
using units::si::constants::C2_wien;
using units::si::electric_potential;
using units::si::volts;
using units::si::milli;

using thermal::pyrometer::twoColor::signalRatio;
using thermal::pyrometer::twoColor::calibratedSignalRatio;
using thermal::pyrometer::twoColor::normalizedSignalRatio;

BOOST_AUTO_TEST_CASE( testA ) {
  
  const auto micrometers = micro * meters;
  
  const double wavelength1Nominal = 4.4;
  const double wavelength2Nominal = 5.4;
  
  const auto wavelength1 = quantity<length>( wavelength1Nominal * micrometers );
  const auto wavelength2 = quantity<length>( wavelength2Nominal * micrometers );
  
  const double signal1Nominal = 3.2;
  const double signal2Nominal = 3.3;
  
  const auto millivolts = milli * volts;
  const auto signal1 = quantity<electric_potential>( signal1Nominal * millivolts );
  const auto signal2 = quantity<electric_potential>( signal2Nominal * millivolts );
  
  
  const auto gCoeff = quantity<dimensionless>( 1.02 );

  const auto rSR = signalRatio( signal1, signal2 );
  
  const auto gSR = calibratedSignalRatio( rSR, gCoeff );

  const auto nSR = normalizedSignalRatio( gSR, wavelength1, wavelength2 ) ;
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
