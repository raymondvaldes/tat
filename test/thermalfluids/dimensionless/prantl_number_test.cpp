//
//  prantl_number_test.cpp
//  tat-test
//
//  Created by Raymond Valdes_New on 2/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//


#define BOOST_TEST_NO_LIB

#include <iostream>

#include <boost/test/unit_test.hpp>

#include "thermalfluids/dimensionless/prandtl_number.h"


BOOST_AUTO_TEST_SUITE( thermalfluids )

BOOST_AUTO_TEST_CASE( prantl_Number )
{
  using thermalfluids::dimensionless::Prandtl_number;

  using units::si::meter;
  using units::si::second;
  
  using units::quantity;
  
  using units::si::thermal_diffusivity;
  using units::si::thermal_diffusivity_units;
  
  using units::si::kinematic_viscosity;
  using units::si::kinematic_viscosity_units;
  
  auto const
  nu = quantity< kinematic_viscosity >
  ( 1.004 * 10e-6 * kinematic_viscosity_units );
  
  auto const
  alpha = quantity< thermal_diffusivity >
  ( 0.143 * 10e-6 * thermal_diffusivity_units );


  BOOST_VERIFY( nu / alpha == Prandtl_number(nu, alpha ) ) ;
}


BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids