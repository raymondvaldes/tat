//
//  offset_measurement_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 8/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//


#define BOOST_TEST_NO_LIB

#include <iostream>
#include <boost/test/unit_test.hpp>
#include "thermal/model/oneLayer2D/thermal_emission/point_measurement.h"
#include "thermal/model/oneLayer2D/thermal_emission/fast_measurement.h"
#include "thermal/model/oneLayer2D/thermal_emission/offset_detector/offset_measurement.hpp"

BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( oneLayer2D )
BOOST_AUTO_TEST_SUITE( thermal_emission )
BOOST_AUTO_TEST_SUITE( offset_detector )

using namespace units;
using thermal::model::oneLayer2D::thermal_emission::point_measurement;
using thermal::model::oneLayer2D::thermal_emission::fast_measurement;
using thermal::model::oneLayer2D::thermal_emission::offset_detector::offset_measurement;


BOOST_AUTO_TEST_CASE( offset_measurmement_test_case )
{
  auto const dT = quantity< si::temperature >::from_value(1.0);
  auto const b1_beamRadius = quantity< si::dimensionless >( 2.5 );
  auto const l_thermal = quantity<si::dimensionless >( 0.2);
  auto const b2_detectorRadius = quantity<si::dimensionless>( 0.1 );
  auto const b3_detectorOffset = quantity<si::dimensionless>( 0.1 );



  auto const center_r0 = quantity<  si::dimensionless >( 0.0 );
  auto const center = point_measurement( b1_beamRadius, l_thermal, dT , center_r0 )

//  auto const center_view = fast_measurement( r, hp, tp , l ) ;
//  auto const offset_view = fast_measurement( r, hp, tp , l ) ;

  std::cout << center.phase << "\n";
  
  
}


BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite

