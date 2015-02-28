//
//  tat-test
//
//  Created by Raymond Valdes on 6/12/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

//#define BOOST_TEST_MODULE tat_unit_test//
//#include <boost/test/included/unit_test.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "math/utility.hpp"

#include <ratio>
#include <array>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <cmath>
#include <istream>

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( utility )



BOOST_AUTO_TEST_CASE( within_tolerance ) {
  using std::abs;
  using math::within_tolerance;
  
  constexpr double tol = 0.0001 ;

  auto const within_tol_checker = [=]( const double val, const double val2 ) {
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

  auto const avg_checker = [ = ]( const double test_case ) {
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

BOOST_AUTO_TEST_CASE( even ) {
  using math::even;
  BOOST_CHECK( even(2) ) ;
  BOOST_CHECK( even(-4) ) ;
  BOOST_CHECK( even(0) ) ;
  BOOST_CHECK( !even(1) ) ;
 
}

BOOST_AUTO_TEST_CASE( odd ) {
  using math::odd;
  
  BOOST_CHECK( odd(3) ) ;
  BOOST_CHECK( odd(7) ) ;
  BOOST_CHECK( odd(9) ) ;
  BOOST_CHECK( !odd(2) ) ;

}

BOOST_AUTO_TEST_CASE( median_of_all ) {
  using std::vector;
  using math::within_tolerance;
  using math::median_of_all;

  const double tol = 0.05 ;
  auto const checker = [tol]( const vector<double> sorted,const double answer){
    const double calc_median = median_of_all( sorted.data(), sorted.size() ) ;
    const bool pass = within_tolerance( calc_median, answer, tol ) ;
    BOOST_CHECK_MESSAGE( pass ,
      "output:" << calc_median << "\t" << answer << "\t" << sorted.size()  ) ;
    return pass ;
  } ;
  
  BOOST_CHECK( checker( {0,1} , 0.5 ) ) ;
  BOOST_VERIFY( checker( {0,6,8} , 6 ) ) ;
  BOOST_VERIFY( checker( {1,2,41,43,99,100 } , 42 ) ) ;
  BOOST_VERIFY( checker( {0,0,0,0,0,0,0,0,0,0,1} , 0 ) ) ;
  BOOST_VERIFY( checker( {-10, -2, -1, 3, 7} , -1 ) ) ;
}




BOOST_AUTO_TEST_CASE( percentilelog10 ) {
  using math::percentilelog10;
  
  const double tol = 1e-10 ;
  
  auto const checker = [tol]( const double min ) {
    const double mid = 10 * min ;
    const double max = 100 * min ;
    
    const double percent_min = 0 ;
    const double percent_max = 1 ;
    const double percent_mid = 0.50 ;
    BOOST_CHECK_CLOSE( percentilelog10( min, max, min ), percent_min, tol ) ;
    BOOST_CHECK_CLOSE( percentilelog10( min, max, max ), percent_max, tol ) ;
    BOOST_CHECK_CLOSE( percentilelog10( min, max, mid ), percent_mid, tol ) ;
  } ;
  
  checker( .01 ) ;
  checker( .001 ) ;
  checker( 1 ) ;
}

BOOST_AUTO_TEST_CASE( CRfromSweepLimits ) {
  typedef const std::pair<double, double> constPairDD ;
  using math::CRfromSweepLimits;
  using std::make_pair;
  
  auto const checker = [] ( constPairDD outer_bounds ) {
    constPairDD fullset = outer_bounds ;
    constPairDD full_calc = CRfromSweepLimits( fullset, outer_bounds ) ;
    const double center = 0.5;
    const double range = 1.0;
    constPairDD full_true = make_pair( center, range ) ;
    
    BOOST_VERIFY( full_true == full_calc ) ;
  } ;

  checker( make_pair( .1, 1 ) ) ;
  checker( make_pair( .01, .02 ) ) ;
  checker( make_pair( 1, 2 ) ) ;
  checker( make_pair( 3, 3.0152 ) ) ;
  checker( make_pair( 5.726, 8.465 ) ) ;
}

//BOOST_AUTO_TEST_CASE( random_CR_from_limits ) {
//
////doesn't matter what limits i give this function, i expect the random CR to
//// vary from 0->1
//  typedef const math::Interval Interval;
//  typedef const std::pair<double, double> constPairDD ;
//  using math::checkLimits;
//  using math::CRfromSweepLimits;
//  using math::average_of_all;
//  using std::make_pair;
//  using std::vector;
//  const int Iters = 5000 ;
//  const double tol = .1;
//
//  auto const checker = [] ( Interval masterInterval ) {
//    Interval subInterval = masterInterval.get_log10_random_subInterval() ;
//  
//    constPairDD myCR =
//      CRfromSweepLimits( subInterval.get_pair() , masterInterval.get_pair() ) ;
//    
//    BOOST_VERIFY( checkLimits( myCR ) ) ;
//    
//    return myCR ;
//  } ;
//
//
//  auto const checkerIterator = [&] ( constPairDD myPair ) {
//    vector< double > Centers(Iters) ;
//    vector< double > Ranges(Iters) ;
//    for( int i = 0 ; i < Iters ; ++i ) {
//      constPairDD myCR = checker( Interval( myPair ) ) ;
//      Centers[i] = myCR.first ;
//      Ranges[i] = myCR.second ;
//    }
//    const double center_avg = average_of_all( Centers.data(), Iters ) ;
//    const double range_avg = average_of_all( Ranges.data(), Iters ) ;
//    const double expected_avg = 0.50 ;
//    const double expected_rag = 0.33 ;
//    
//    BOOST_CHECK_CLOSE_FRACTION( center_avg, expected_avg, tol ) ;
//    BOOST_CHECK_CLOSE_FRACTION( range_avg, expected_rag, tol ) ;
//  } ;
//  
//  checkerIterator( make_pair(.05, 20 ) ) ;
//  checkerIterator( make_pair( 10, 20 ) ) ;
//  checkerIterator( make_pair( 1, 1.5 ) ) ;
//}

BOOST_AUTO_TEST_CASE( checkLimits ) {
  using math::checkLimits;
  
  auto const checker = [] ( const double center ) {
    const double rangemax = ( center > 0.5 ) ? 2 * ( 1 - center ) : center * 2 ;

    constexpr double tol = .00001;
    BOOST_VERIFY( checkLimits( center, rangemax ) ) ;
    BOOST_VERIFY( checkLimits( center, tol ) ) ;
    BOOST_VERIFY( checkLimits( center, rangemax / 2 ) ) ;
    BOOST_VERIFY( !checkLimits( center, rangemax + tol ) ) ;

    BOOST_VERIFY( !checkLimits( center, rangemax * 2 ) ) ;
    BOOST_VERIFY( !checkLimits( center, rangemax * 1.01 ) ) ;
  } ;

  checker( 0.7 ) ;
  checker( 0.3 ) ;
  checker( 0.5 ) ;
  checker( 0.99 ) ;
  checker( 0.01 ) ;
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()