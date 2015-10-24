//
//  sum_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vector>

#include "statistics/signal_processing/sum.h"
#include "units.h"

using statistics::signal_processing::sum;
using std::vector;
using namespace units;
BOOST_AUTO_TEST_SUITE( statistics )
BOOST_AUTO_TEST_SUITE( signal_processing )

BOOST_AUTO_TEST_CASE( sum_test_1 )
{
  auto const a = quantity< plane_angle >( 1 * radians ) ;
  auto const b = quantity< plane_angle >( 2 * radians ) ;
  auto const c = quantity< plane_angle >( 3 * radians ) ;
  auto const list = vector< quantity< plane_angle> >( {a, b , c} );

  auto const summation = sum( list );
  
  BOOST_CHECK_CLOSE_FRACTION( summation.value() , 6 , 1e-10);

}

BOOST_AUTO_TEST_CASE( sum_test_initializer_list )
{
  auto const a = quantity< plane_angle >( 1 * radians ) ;
  auto const b = quantity< plane_angle >( 2 * radians ) ;
  auto const c = quantity< plane_angle >( 3 * radians ) ;

  auto const summation = sum( {a,b,c} );
  
  BOOST_CHECK_CLOSE_FRACTION( summation.value() , 6 , 1e-10);

}

BOOST_AUTO_TEST_CASE( sum_test_1_double )
{
  auto const a = quantity< plane_angle >( 1.1 * radians ) ;
  auto const b = quantity< plane_angle >( 2.2 * radians ) ;
  auto const c = quantity< plane_angle >( 3.3 * radians ) ;
  auto const list = vector< quantity< plane_angle> >( {a, b , c} );

  auto const summation = sum( list );
  
  BOOST_CHECK_CLOSE_FRACTION( summation.value() , 6.6 , 1e-10);

}

BOOST_AUTO_TEST_CASE( sum_test_initializer_list_double )
{
  auto const a = quantity< plane_angle >( 1.1 * radians ) ;
  auto const b = quantity< plane_angle >( 2.2 * radians ) ;
  auto const c = quantity< plane_angle >( 3.3 * radians ) ;
//  auto const list = vector< quantity< plane_angle> >( {a, b , c} );

  auto const summation = sum( {a,b,c} );
  
  BOOST_CHECK_CLOSE_FRACTION( summation.value() , 6.6 , 1e-10);

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
