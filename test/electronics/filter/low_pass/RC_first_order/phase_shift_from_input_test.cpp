//
//  phase_shift_from_input.cpp
//  tat-test
//
//  Created by Raymond Valdes on 9/1/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//


#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>
#include <vector>

#include "units.h"
#include "electronics/filter/low-pass/RC-first-order/phase_shifts_from_input.hpp"
#include "physics/classical_mechanics/kinematics.h"

using namespace units;
using std::vector;
using physics::classical_mechanics::frequency_to_angularFrequency;
using physics::classical_mechanics::angularFrequencies_from_frequencies;
using electronics::filter::low_pass::RC_first_order::phase_shifts_from_input;

BOOST_AUTO_TEST_SUITE( electronics )
BOOST_AUTO_TEST_SUITE( filter )
BOOST_AUTO_TEST_SUITE( low_pass )
BOOST_AUTO_TEST_SUITE( RC_first_order )


BOOST_AUTO_TEST_CASE( phases_from_input_test )
{
  auto const R = quantity< electrical_resistance >( 50000. * ohms  );
  auto const C = quantity< electrical_capacitance >( 40.0 * picofarads );
  auto const tau = R * C;

  auto const frequencies = vector< quantity< frequency > >({
    1.0 * hertz,
    128 * hertz,
    11583.488 * hertz
  });
    
  auto const omegas = angularFrequencies_from_frequencies( frequencies );
  
  auto const phase_radians_excel = vector< quantity< plane_angle > > ({
    -0.0000125663706136977 * radians,
    -0.0016084940514427900 * radians,
    -0.1445471998416510000 * radians
  });
  
  auto const phase_shifts = phase_shifts_from_input( frequencies, tau );
  
  
  BOOST_CHECK_CLOSE_FRACTION( phase_shifts[0].value(), phase_radians_excel[0].value(), 1e-11);
  BOOST_CHECK_CLOSE_FRACTION( phase_shifts[1].value(), phase_radians_excel[1].value(), 1e-11);
  BOOST_CHECK_CLOSE_FRACTION( phase_shifts[2].value(), phase_radians_excel[2].value(), 1e-11);

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

