//
//  phase_shift_from_input.cpp
//  tat-test
//
//  Created by Raymond Valdes on 9/1/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//


#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

#include "units.h"
#include "electronics/filter/low-pass/RC-first-order/phase_shift_from_input.hpp"
#include "physics/classical_mechanics/kinematics.h"

using namespace units;
using physics::classical_mechanics::frequency_to_angularFrequency;
using electronics::filter::low_pass::RC_first_order::phase_shift_from_input;

BOOST_AUTO_TEST_SUITE( electronics )
BOOST_AUTO_TEST_SUITE( filter )
BOOST_AUTO_TEST_SUITE( low_pass )
BOOST_AUTO_TEST_SUITE( RC_first_order )


BOOST_AUTO_TEST_CASE( phase_from_input_test )
{
  auto const R = quantity< electrical_resistance >( 50000. * ohms  );
  auto const C = quantity< electrical_capacitance >( 40.0 * picofarads );

  auto const tau = R * C;
  BOOST_CHECK_CLOSE_FRACTION( 1./tau.value() , 500000 , 1e-10);


  auto const frequency = 11583.488 * hertz;
  auto const omega = frequency_to_angularFrequency( frequency );
  
  
  auto const argument = omega * tau ;
  

  auto const phase_radians = -atan( omega * tau / radians ) * radians ;
  auto const phase_calculated = -0.14454719984165100;

  auto const phase_function = phase_shift_from_input( frequency, tau );
  
  
  BOOST_CHECK_CLOSE_FRACTION( phase_calculated, phase_radians.value(), 1e-12);
  
  BOOST_CHECK_CLOSE_FRACTION(
    phase_function.value(), phase_radians.value(), 1e-12);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

