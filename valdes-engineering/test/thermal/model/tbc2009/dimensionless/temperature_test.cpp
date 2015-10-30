//
//  temperature_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "thermal/model/tbc2009/dimensionless/temperature.h"


BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( tbc2009 )
BOOST_AUTO_TEST_SUITE( dimensionless )


BOOST_AUTO_TEST_CASE( temperature_test )
{
  using namespace units;
  using std::complex;
  using namespace std::literals;
  
  auto const theta = quantity< si::dimensionless, complex<double>>( 2.+3.i );
  auto const L = quantity<length>( .2 * micrometers );
  auto const I_o = quantity<heat_flux>( 1.1 * watts/square_meter );
  auto const R0 = quantity< si::dimensionless>( .2 );
  auto const k = quantity<thermal_conductivity >( 2.3 * watts / meter / kelvin );

  
  using thermal::model::tbc2009::dimensionless::temperature;
  
  auto const eval = temperature( theta, L, I_o, R0 , k );
  auto const tol = 1e10-15;
  
  auto const theta_val = theta.value();
  auto const L_val = L.value();
  auto const Io_val = I_o.value();
  auto const R0_val = R0.value();
  auto const k_val = k.value();
  
  auto const temp = theta_val / ( L_val * Io_val * ( 1- R0_val ) / k_val );
  
  BOOST_CHECK_CLOSE_FRACTION(  temp.real() , eval.value().real(), tol ) ;
  BOOST_CHECK_CLOSE_FRACTION(  temp.imag() , eval.value().imag(), tol ) ;

}


BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
BOOST_AUTO_TEST_SUITE_END()  // suite thermalfluids
