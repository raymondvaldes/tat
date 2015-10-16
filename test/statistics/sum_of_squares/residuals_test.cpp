//
//  residuals.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/6/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//


#include "statistics/sum_of_squares/residuals.h"
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>
#include <vector>

#include "units.h"

namespace sum_of_squares = statistics::sum_of_squares;
using std::vector;
using namespace units;

BOOST_AUTO_TEST_SUITE( statistics )
BOOST_AUTO_TEST_SUITE( sum_of_squares )


BOOST_AUTO_TEST_CASE( test_1 )
{
  auto const a = vector<double>({ 1,2,3,4,5 } );
  auto const b = a;
  
  auto const ss_residuals = statistics::sum_of_squares::residuals( a, b );
  
//  BOOST_CHECK_CLOSE_FRACTION( ss_residuals , 0 , 1);

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

