//
//  random.cpp
//  tat-test
//
//  Created by Raymond Valdes on 6/27/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include "math/random/random.h"
#include "math/utility.hpp"

using std::vector ;
using std::array ;
using std::sort ;
using std::none_of;
using math::within_tolerance;
using math::average_of_all ;
using math::median_of_all ;

BOOST_AUTO_TEST_SUITE( random_stuff )


//BOOST_AUTO_TEST_CASE( random_0_to_1 ) {
//  using math::random_0_to_1 ;
//
//
//  constexpr double min = 0 ;
//  constexpr double mid = 0.5;
//  constexpr double max = 1 ;
//  constexpr size_t units = 500 ;
//  constexpr double tol = 0.05 ;
//  
//  array<double, units> out;
//  for( auto& output: out ) {
//    output = random_0_to_1() ;
//  }
//  sort ( out.begin(), out.end() ) ;
//  
//  auto const less_min = []( const double i ){ return i < min ; } ;
//  const bool none_less_min = none_of( out.begin(), out.end(), less_min ) ;
//  BOOST_CHECK( none_less_min ) ;
//
//  auto const greater_max = []( const double i ){ return i > max ; } ;
//  const bool none_greater_max = none_of( out.begin(), out.end(), greater_max ) ;
//  BOOST_CHECK( none_greater_max) ;
//
//  const bool smallest_is_min = within_tolerance ( out.front(), min, tol );
//  BOOST_VERIFY( smallest_is_min ) ;
//  
//  const bool largest_is_max = within_tolerance ( out.back(), max, tol ) ;
//  BOOST_VERIFY( largest_is_max ) ;
//
//  const double avg = average_of_all( out.data(), out.size() ) ;
//  const bool avg_is_midpoint = within_tolerance( avg, mid, tol ) ;
//
//  BOOST_VERIFY( avg_is_midpoint );        // #1 continues on error
//}

//BOOST_AUTO_TEST_CASE( random_in_logspace ) {
//  using math::random_in_logspace ;
//
//  constexpr size_t units = 1000;
//  constexpr double tol = 0.2 ;
//  
//  auto const rand_checker = [tol, units]( const double min ) {
//  const double mid = min * 10 ;
//  const double max = min * 100 ;
//
//  vector<double> out(units);
//  for( auto& output: out ) {
//    output = random_in_logspace( min, max ) ;
//  }
//  
//  sort ( out.begin(), out.end() ) ;
//  
//  const bool none_less_than_min = out.front() > min  ;
//  BOOST_CHECK( none_less_than_min ) ;
//
//  const bool none_greater_than_max = out.back() < max ;
//  BOOST_CHECK( none_greater_than_max) ;
//
//  
//  BOOST_CHECK_CLOSE_FRACTION( out.front(), min, tol ) ;
//  BOOST_CHECK_CLOSE_FRACTION( out.back(), max, tol ) ;
//
//  const double median = median_of_all( out.data(), out.size() ) ;
//  BOOST_CHECK_CLOSE_FRACTION( median, mid, tol ) ;
//  };
//  
//  rand_checker( .02 ) ;
//}

BOOST_AUTO_TEST_SUITE_END()
