//
//  integrate_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 3/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

#include "math/numIntegration/integrate.h"
#include "units.h"

using namespace units;
using std::vector;
using math::numIntegration::integrate;


BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( numIntegrate )


BOOST_AUTO_TEST_CASE( integrate_test_2 )
{
  //func_type const & func,
  
  auto const x0 = double(0.);
  auto const x1 = double( 0.5 );
  auto const dx_intial_step = double( 0.1 );

  // given integrate f(x) from a to b.  Must satisfy F(a) = 0;
  auto const f_x0 = vector< double > ( { 0 } );
  auto const func = []
  (
    vector< double > const & y,
    vector< double > & dy,
    double const x
  ) noexcept -> void
  {
    dy[0] = x ;
  };

  auto const area_under_curve =
  math::numIntegration::integrate( func, f_x0, x0, x1, dx_intial_step );
  
  BOOST_CHECK_CLOSE( area_under_curve, 0.125 , 1e-10);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()