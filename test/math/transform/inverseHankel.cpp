//
//  inverseHankel.cpp
//  tat-test
//
//  Created by Raymond Valdes on 4/25/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>
#include "units.h"
#include "math/transform/inverseHankel.h"

using math::transform::inverseHankel;
using namespace units;
using std::abs;
using std::pow;
using std::exp;

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( transform )

BOOST_AUTO_TEST_CASE( inverse_hankel_simple )
{
  auto const h = []
  ( quantity<dimensionless> const r ) noexcept
  {
    return exp( - pow<2>(r) ) ;
  };
  
  auto const h_transformed = []( auto const s ) noexcept {
    auto const val = exp( - pow( s, 2) / 4.0  ) / 2.0 ;
    return quantity<dimensionless>( val );
  };
  
  auto const test = [&h, &h_transformed]( auto const r_val )
  {
    auto const r = quantity<dimensionless>( r_val ) ;
    auto const exact = h_transformed( r_val ) ;
    auto const calculated = inverseHankel( h, r ) ;
    
    auto const small_tol = 1e-9;
    auto const calc_small = abs( calculated.value() ) < small_tol;
    auto const exact_small = abs( exact.value() ) < small_tol;
    
    auto const both_small = calc_small && exact_small ;
    if( !both_small ) {
      BOOST_CHECK_CLOSE_FRACTION( calculated.value(), exact.value(), small_tol );
    }
  };

  test( 0.0001 ) ;
  test( 0.001 ) ;
  test( 0.01 ) ;
  test( 0.1 ) ;
  test( 1.0 ) ;
  test( 9.0 ) ;
  test( 10.0 ) ;
  test( 100.0 ) ;
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
