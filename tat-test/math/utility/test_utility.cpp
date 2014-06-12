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
  constexpr double A1 = -10.00 ;
  constexpr double A2 = -10.1 ;

  const double forwarddiff = abs( A1 - A2 ) ;
  const double backwarddiff = abs( A2 - A1 ) ;
  
  const bool trueAnswer1 = forwarddiff < tol ;
  const bool trueAnswer2 = backwarddiff < tol ;

  BOOST_CHECK( within_tolerance( A1, A2, tol ) == trueAnswer1 ) ;
  BOOST_CHECK( within_tolerance( A2, A1, tol ) == trueAnswer2 ) ;
}

BOOST_AUTO_TEST_CASE( average_of_all ) {
  using std::vector;
  using std::abs;
  using math::average_of_all;
  using math::within_tolerance;
  
  constexpr size_t size = 99 ;
  
  constexpr double caseA = 24 ;
  constexpr double caseB = 0.24 ;
  constexpr double caseC = -.50 ;
  constexpr double tol = .02 ;

  vector<double> caseAarray(size) ;
  vector<double> caseBarray(size) ;
  vector<double> caseCarray(size) ;
  for( size_t i = 0 ; i < size ; ++i ) {
    caseAarray[i] = ( double(i) / ( size - 1 ) ) * caseA ;
    caseBarray[i] = ( double(i) / ( size - 1 ) ) * caseB ;
    caseCarray[i] = ( double(i) / ( size - 1 ) ) * caseC ;

  }

  const double true_avg_A = caseA / 2 ;
  const double true_avg_B = caseB / 2 ;
  const double true_avg_C = caseC / 2 ;
  
  const double calc_avg_A = average_of_all(caseAarray.data(),caseAarray.size());
  const double calc_avg_B = average_of_all(caseBarray.data(),caseBarray.size());
  const double calc_avg_C = average_of_all(caseCarray.data(),caseCarray.size());

  const bool caseAtest = within_tolerance(calc_avg_A,true_avg_A,abs(true_avg_A*tol));
  const bool caseBtest = within_tolerance(calc_avg_B,true_avg_B,abs(true_avg_B*tol));
  const bool caseCtest = within_tolerance(calc_avg_C,true_avg_C,abs(true_avg_C*tol));


  BOOST_CHECK_MESSAGE( caseAtest , true_avg_A << calc_avg_A ) ;
  BOOST_CHECK_MESSAGE( caseBtest , true_avg_B << calc_avg_B ) ;
  BOOST_CHECK_MESSAGE( caseCtest , true_avg_C << calc_avg_C ) ;

}

