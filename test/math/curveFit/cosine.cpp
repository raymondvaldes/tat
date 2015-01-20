//
//  cosine.cpp
//  tat-test
//
//  Created by Raymond Valdes on 1/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/curveFit/cosine.h"

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

  using std::vector;
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

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( curveFit )

struct periodicProperties {
  quantity< electric_potential > offset =  0 * volts  ;
  quantity< electric_potential > amplitude = 1.0 * volts ;
  quantity< angular_frequency > omega = 1.0 * radians_per_second ;
  quantity< plane_angle > phase = 0 * radians ;
  
} ;

BOOST_FIXTURE_TEST_SUITE( cosine_fitting, periodicProperties )


BOOST_AUTO_TEST_CASE( cosine_fit_constructor )
{

  auto myVectVolts = vector< quantity< electric_potential > >();
  
  auto myTimeVector = vector< quantity< units::si::time > >( );
  
  using namespace math::curveFit;
//  curveFit::cosine( myTimeVector, myVectVolts,  );

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
