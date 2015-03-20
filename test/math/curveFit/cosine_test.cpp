//
//  cosine.cpp
//  tat-test
//
//  Created by Raymond Valdes on 1/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB

#include <algorithm>
#include <iostream>

#include "algorithm/algorithm.h"
#include "math/curveFit/cosine.h"
#include "math/construct/range.h"
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

using algorithm::generate;
using algorithm::transform;

using std::vector;
using units::quantity;
using namespace units::si;

using math::functions::Periodic;
using math::functions::PeriodicProperties;
using math::construct::range_from_0;

BOOST_AUTO_TEST_SUITE( math )

BOOST_AUTO_TEST_SUITE( curveFit )

struct InternalperiodicProperties {
  quantity< electric_potential > offset =  100 * volts  ;
  quantity< electric_potential > amplitude = 0.01 * volts ;
  quantity< plane_angle > phase = -1.5 * radians ;
  
  quantity< angular_frequency > omega = 2.5 * radians_per_second ;
  quantity< frequency > myFrequency = omega /  ( M_PI * radians ) ;
  quantity< units::si::time > period = quantity<dimensionless>(1) / myFrequency;

  quantity< electric_potential > offset_initial =  5 * volts  ;
  quantity< electric_potential > amplitude_initial = 2.0 * volts ;
  quantity< plane_angle > phase_initial = -0.1 * radians ;
  
} ;

BOOST_FIXTURE_TEST_SUITE( cosine_fitting_test, InternalperiodicProperties )


BOOST_AUTO_TEST_CASE( cosine_fit_test )
{
  auto const tol = 1e-10;
  auto const points = 101;
  
  auto const myTime = range_from_0( period, points );
  auto const phase_offset = quantity<plane_angle>( -M_PI_2 * radians );
 
  auto myVectVolts = vector< quantity< electric_potential > >( points );
  
  transform( myTime, myVectVolts.begin(), [&]( auto const t )
  {
    return offset + amplitude * cos( omega * t + phase + phase_offset );
  });

  auto const initialConditions =
  PeriodicProperties<electric_potential>
  ( offset_initial, amplitude_initial, omega, phase_initial );
  
  using namespace math::curveFit;
  auto const f_cosine =
  curveFit::cosine( myTime, myVectVolts, initialConditions, phase_offset );

  
  BOOST_CHECK_CLOSE_FRACTION( omega.value(), f_cosine.omega.value(), tol );
  BOOST_CHECK_CLOSE_FRACTION( amplitude.value(),f_cosine.amplitude.value(),tol);
  BOOST_CHECK_CLOSE_FRACTION( offset.value(), f_cosine.offset.value(), tol ) ;
  BOOST_CHECK_CLOSE_FRACTION( phase.value(), f_cosine.phase.value(), tol );
}

BOOST_AUTO_TEST_SUITE_END() // cosine_fitting_test
BOOST_AUTO_TEST_SUITE_END() // curveFit
BOOST_AUTO_TEST_SUITE_END() // math
