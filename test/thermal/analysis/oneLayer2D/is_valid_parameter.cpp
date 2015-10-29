//
//  is_valid_parameter.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//


#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "thermal/model/oneLayer2D/is_valid_parameters.hpp"


using thermal::model::oneLayer2D::is_valid_parameters;
using thermal::model::oneLayer2D::Parameters;

BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( analysis )
BOOST_AUTO_TEST_SUITE( oneLayer2D )

BOOST_AUTO_TEST_CASE( check_subset )
{
  auto const sample = Parameters({
    thermal::model::oneLayer2D::Parameter::disk_thermal_diffusivity,
    thermal::model::oneLayer2D::Parameter::disk_radius,
    thermal::model::oneLayer2D::Parameter::detector_radius,
    thermal::model::oneLayer2D::Parameter::rc_filter
  });

  auto const valid_set = Parameters({
    thermal::model::oneLayer2D::Parameter::disk_thermal_diffusivity,
    thermal::model::oneLayer2D::Parameter::disk_radius,
    thermal::model::oneLayer2D::Parameter::detector_radius,
    thermal::model::oneLayer2D::Parameter::rc_filter
  });

  auto const pass = is_valid_parameters( sample, valid_set ) ;
  
  BOOST_CHECK( pass );

}


BOOST_AUTO_TEST_SUITE_END()  // suite detector
BOOST_AUTO_TEST_SUITE_END()  // suite equipment
BOOST_AUTO_TEST_SUITE_END()  // suite thermal

