//
//  PeriodData_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/6/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//


#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>
#include "math/functions/PeriodicProperties.h"
#include "math/functions/PeriodicData.h"
#include "math/functions/cosine.h"
#include "units.h"

using namespace units;
using math::functions::PeriodicProperties;
using math::functions::PeriodicData;
  using math::functions::Cosine;

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( functions )

struct periodicProperties {
  quantity< electric_potential > offset =  200 * volts  ;
  quantity< electric_potential > amplitude = 1.0 * volts ;
  quantity< angular_frequency > omega = 1.0 * radians_per_second ;
  quantity< plane_angle > phase = 1.2 * radians ;
  
  PeriodicProperties< electric_potential >
  myProperties = PeriodicProperties< electric_potential >
  ( offset, amplitude, omega, phase ) ;
  
} ;

BOOST_FIXTURE_TEST_SUITE( periodicData, periodicProperties)

BOOST_AUTO_TEST_CASE( estimate_offset_test ) {

  auto const cosFunc =
  Cosine<electric_potential>( myProperties ) ;
  
  auto const N_periods = 1;
  auto const N_values = 50;
  auto const data = cosFunc.evaluate_for_n_periods( N_periods, N_values );
  
  auto const pdata = PeriodicData< electric_potential >( data ) ;

  auto const estimate = pdata.initialEstimateOffset();
  
  BOOST_CHECK_CLOSE_FRACTION( estimate.value() , offset.value() , 1e-3 ) ;
}

BOOST_AUTO_TEST_CASE( estimate_amplitude_test ) {

  auto const cosFunc =
  Cosine<electric_potential>( myProperties ) ;
  
  auto const N_periods = 3;
  auto const N_values = 199;
  auto const data = cosFunc.evaluate_for_n_periods( N_periods, N_values );
  
  auto const pdata = PeriodicData< electric_potential >( data ) ;

  auto const estimate = pdata.initialEstimateAmplitude();
  
  BOOST_CHECK_CLOSE_FRACTION( estimate.value() , amplitude.value() , 1e-3 ) ;
  
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
