//
//  periodic.cpp
//  tat-test
//
//  Created by Raymond Valdes on 1/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/functions/periodic.h"
#include "math/functions/sine.h"
#include "math/functions/cosine.h"

#include "units/units.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( functions )

using units::quantity;
using units::si::electric_potential;
using units::si::angular_frequency;
using units::si::radians;
using units::si::radians_per_second;
using units::si::plane_angle;
using units::si::volts;
using units::si::seconds;

using units::si::milli;
const auto millivolts = milli * volts;
using math::functions::Periodic;


struct periodicProperties {
  quantity< electric_potential > offset =  0 * volts  ;
  quantity< electric_potential > amplitude = 1.0 * volts ;
  quantity< angular_frequency > omega = 1.0 * radians_per_second ;
  quantity< plane_angle > phase = 0 * radians ;
  
} ;

BOOST_FIXTURE_TEST_SUITE( periodic, periodicProperties)


BOOST_AUTO_TEST_CASE( sine_function ) {

  using math::functions::Sine;
  auto sinFunc =
  Sine<electric_potential>( offset, amplitude, omega, phase ) ;

  using std::sin;
  BOOST_CHECK_CLOSE( sinFunc( 0.1 * seconds ).value() , sin( 0.1 ) , 1e-14 ) ;
  BOOST_CHECK_CLOSE( sinFunc( -0.1 * seconds ).value() , sin( -0.1 ) , 1e-14 ) ;
  BOOST_CHECK_CLOSE( sinFunc( 0 * seconds ).value() , sin( 0 ) , 1e-14 ) ;
  

}

BOOST_AUTO_TEST_CASE( cosine_function ) {

  using math::functions::Cosine;
  const auto cosFunc =
  Cosine<electric_potential>( offset, amplitude, omega, phase ) ;

  using std::cos;
  cosFunc( 0.1 * seconds ).value();
  BOOST_CHECK_CLOSE( cosFunc( 0.1 * seconds ).value() , cos( 0.1 ) , 1e-14 ) ;
  BOOST_CHECK_CLOSE( cosFunc( -0.1 * seconds ).value() , cos( -0.1 ) , 1e-14 ) ;
  BOOST_CHECK_CLOSE( cosFunc( 0 * seconds ).value() , cos( 0 ) , 1e-14 ) ;
  

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
