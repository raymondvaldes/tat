//
//  abs.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/6/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//


#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vector>
#include <cmath>

#include "statistics/signal_processing/abs.h"
#include "units.h"

using statistics::signal_processing::abs;
using std::vector;
using namespace units;
using std::abs;
using units::abs;

BOOST_AUTO_TEST_SUITE( statistics )
BOOST_AUTO_TEST_SUITE( signal_processing )



BOOST_AUTO_TEST_CASE( abs_vector_t )
{
  auto const a = 1.1 ;
  auto const b = -2.2 ;
  auto const c = 3.3 ;
  auto const list = vector< double >( {a, b , c} );

  auto const list_abs = abs(  list );
  
  for( auto const l : list_abs ) {
    BOOST_CHECK_CLOSE_FRACTION( l , std::abs(l) , 1e-10);
  
  }
  

}

BOOST_AUTO_TEST_CASE( abs_vector_quantities )
{
  auto const a = quantity< plane_angle >( 1.1 * radians ) ;
  auto const b = quantity< plane_angle >( -2.2 * radians ) ;
  auto const c = quantity< plane_angle >( 3.3 * radians ) ;
  auto const list = vector< quantity< plane_angle> >( {a, b , c} );

  auto const list_abs = abs(  list );
  
//
//  BOOST_CHECK_CLOSE_FRACTION( list_abs[0] , abs( a ) , 1e-10 );
//  BOOST_CHECK_CLOSE_FRACTION( list_abs[1] , abs( b ) , 1e-10 );
//  BOOST_CHECK_CLOSE_FRACTION( list_abs[2] , abs( c ) , 1e-10 );
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

