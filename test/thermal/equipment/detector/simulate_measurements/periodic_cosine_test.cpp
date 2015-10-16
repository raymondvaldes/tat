//
//  periodic_cosine_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/5/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB

#include <iostream>

#include <boost/test/unit_test.hpp>
#include "thermal/equipment/detector/simulate_measurements/periodic_cosine.h"
#include "math/functions/PeriodicProperties.h"
#include "units.h"
#include "math/construct/periodic_time_distribution.h"
#include "cout/vector/print.h"


using namespace units;
using math::functions::PeriodicProperties;
using thermal::equipment::detector::simulate_measurements::periodic_cosine;
using math::construct::periodic_time_distribution;

BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( equipment )
BOOST_AUTO_TEST_SUITE( detector )
BOOST_AUTO_TEST_SUITE( simulate_measurements )

BOOST_AUTO_TEST_CASE( periodic_cosine_test_one )
{
  quantity< electric_potential > offset =  200 * volts  ;
  quantity< electric_potential > amplitude = 1.0 * volts ;
  quantity< angular_frequency > omega = 1.0 * radians_per_second ;
  auto const frequency_temp = 1.0 * hertz;
  quantity< plane_angle > phase = 0 * radians ;
  
  auto const
  properties = PeriodicProperties< electric_potential >
  ( offset, amplitude, frequency_temp, phase ) ;

  
  auto const detector_wavelength = quantity<wavelength>( 4.1 * micrometers );
  auto const points = 10;
  
  auto const frequency = properties.get_temporalFrequency();

  auto const times = periodic_time_distribution( frequency , points );
  

//  auto const E_1 = planks_law( T , lambda );
//  BOOST_CHECK_CLOSE_FRACTION( E_1.value(),  6.92e10 , 1e-3 );
  
}

BOOST_AUTO_TEST_SUITE_END()  // suite simulate_measurements
BOOST_AUTO_TEST_SUITE_END()  // suite detector
BOOST_AUTO_TEST_SUITE_END()  // suite equipment
BOOST_AUTO_TEST_SUITE_END()  // suite thermal

