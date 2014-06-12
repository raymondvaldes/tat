//
//  tat-test
//
//  Created by Raymond Valdes on 6/12/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_MODULE math_utility
#include <boost/test/included/unit_test.hpp>
#include "math/utility.hpp"

#include <array>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <cmath>
#include <istream>

BOOST_AUTO_TEST_CASE( random_0_to_1 ) {
  using std::array ;
  using std::sort ;
  using std::none_of;
  using math::within_tolerance;
  using math::random_0_to_1 ;
  using math::average_of_all ;

  constexpr double min = 0 ;
  constexpr double mid = 0.5;
  constexpr double max = 1 ;
  constexpr size_t units = 1000 ;
  constexpr double tol = 0.025 ;
  
  array<double, units> out;
  for( auto& output: out ) {
    output = random_0_to_1() ;
  }
  sort ( out.begin(), out.end() ) ;
  
  const auto less_than_min = []( const double i ){ return i < min ; } ;
  const bool none_less_than_min = none_of( out.begin(), out.end(), less_than_min ) ;
  BOOST_CHECK( none_less_than_min ) ;

  const auto greater_than_max = []( const double i ){ return i > max ; } ;
  const bool none_greater_than_max = none_of( out.begin(), out.end(), greater_than_max ) ;
  BOOST_CHECK( none_greater_than_max) ;

  const bool smallest_is_min = within_tolerance ( out.front(), min, tol );
  BOOST_VERIFY( smallest_is_min ) ;
  
  const bool largest_is_max = within_tolerance ( out.back(), max, tol ) ;
  BOOST_VERIFY( largest_is_max ) ;

  const double avg = average_of_all( out.data(), out.size() ) ;
  const bool avg_is_midpoint = within_tolerance( avg, mid, tol ) ;
  //const double smallest =
  //const double biggest = outputs
  BOOST_VERIFY( avg_is_midpoint );        // #1 continues on error
}

BOOST_AUTO_TEST_CASE( within_tolerance ) {
  using std::abs;
  using math::within_tolerance;
  
  constexpr double tol = 0.0001 ;

  const auto within_tol_checker = [=]( const double val, const double val2 ) {
    const double diff = abs( val - val2 ) ;
    const bool trueAnswer = diff < tol ;
    const bool pass = within_tolerance( val, val2, tol ) == trueAnswer ;
    return pass ;
  } ;

  BOOST_CHECK( within_tol_checker( -10.0, -10.000001 ) ) ;  // close numbers
  BOOST_CHECK( within_tol_checker( -10.1, 0 ) ) ;           // zero with neg
  BOOST_CHECK( within_tol_checker( 5, 6 ) ) ;               // diff int
  BOOST_CHECK( within_tol_checker( -5, 6 ) ) ;              // neg,pos
  BOOST_CHECK( within_tol_checker( 105.12, 105.12 ) ) ;     // same double
  BOOST_CHECK( within_tol_checker( 6, 6 ) ) ;               // same int
}

BOOST_AUTO_TEST_CASE( average_of_all ) {
  using std::vector;
  using std::abs;
  using math::average_of_all;
  using math::within_tolerance;
  
  constexpr size_t size = 99 ;
  constexpr double tol_rel = .02 ;

  const auto avg_checker = [ = ]( const double test_case ) {
    vector<double> scalefunc( size ) ;

    for( size_t i = 0 ; i < size ; ++i ) {
      scalefunc[i] = ( double(i) / ( size - 1 ) ) * test_case ;
    }
    
    const double calc_avg = average_of_all( scalefunc.data(), scalefunc.size());
    const double true_avg = test_case / 2 ;
    const double tol_abs = abs( true_avg ) * tol_rel ;
    
    const bool pass = within_tolerance( calc_avg, true_avg, tol_abs ) ;
    return pass ;
  } ;
  
  BOOST_CHECK( avg_checker( 24 ) ) ;
  BOOST_CHECK( avg_checker( 0.24 ) ) ;
  BOOST_CHECK( avg_checker( -.50 ) ) ;
  BOOST_CHECK( avg_checker( 3 ) ) ;
  BOOST_CHECK( avg_checker( -4 ) ) ;
  BOOST_CHECK( avg_checker( .0001 ) ) ;
}

