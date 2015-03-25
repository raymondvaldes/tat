//
//  wrap_to_0_2Pi_test.cpp
//  tat-test
//
//  Created by Raymond Valdes_New on 3/17/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

#include "math/coordinate_system/wrap_to_0_2Pi.h"
#include "units.h"

using units::quantity;
using units::si::plane_angle;
using units::si::radians;
using math::coordinate_system::wrap_to_0_2Pi;

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( coordinate_system )

BOOST_AUTO_TEST_CASE( wrap_to_0_2Pi_test )
{
  auto const Pi = quantity< plane_angle >(  M_PI * radians );
  auto const threePi = quantity< plane_angle >( 3 * M_PI * radians );
  auto const neg_threePi = quantity< plane_angle >( 3 * M_PI * radians );
  
  BOOST_CHECK_CLOSE( Pi.value(), wrap_to_0_2Pi(threePi).value(), 1e10-10);
  BOOST_CHECK_CLOSE( Pi.value(), wrap_to_0_2Pi(neg_threePi).value(), 1e10-10);

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
