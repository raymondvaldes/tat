//
//  bessel_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <cmath>


#include "math/special_functions/bessel.h"
#include "units.h"

using namespace units;
using std::abs;
using math::special_functions::bessel_j;

BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( special_functions )

BOOST_AUTO_TEST_CASE( bessel_test_case )
{
  size_t const v1 = 0;
  
  auto const x1 = double( 2.3123 );
  auto const x2 = quantity<dimensionless>( x1 );
  
  auto const r0 = bessel_j( 0, x2 ) ;
  auto const r1 = bessel_j( 1, x2 ) ;
  auto const r2 = bessel_j( 2, x2 ) ;
  
  //calculated using wolfram alpha (
  auto const r0_wa =
  quantity<dimensionless>(0.0489130183781769214723562729626210818047575292740605);

  auto const r1_wa =
  quantity<dimensionless>(0.5376413580131548298653732412135844073835890659703832);
  
  auto const r2_wa =
  quantity<dimensionless>(0.4161143206463050487437690059489253502184133966182399);
  
  BOOST_CHECK_CLOSE( r0_wa.value(), r0.value(), 1e-13);
  BOOST_CHECK_CLOSE( r1_wa.value(), r1.value(), 1e-13);
  BOOST_CHECK_CLOSE( r2_wa.value(), r2.value(), 1e-13);
}

BOOST_AUTO_TEST_CASE( bessel_0_small_test_range )
{

  auto const r3s = bessel_j( 0, 1e-8_nd ) ;
  auto const r2s = bessel_j( 0, 1e-7_nd ) ;
  auto const r1s = bessel_j( 0, 1e-6_nd ) ;
  
  auto const r0 = bessel_j( 0, 0.0_nd ) ;
  
  auto const r1 = bessel_j( 0, 0.00001_nd ) ;
  auto const r2 = bessel_j( 0, 0.0001_nd ) ;
  auto const r3 = bessel_j( 0, 0.001_nd ) ;

  auto const r4 = bessel_j( 0, 0.01_nd ) ;
  auto const r5 = bessel_j( 0, 0.1_nd ) ;
  auto const r6 = bessel_j( 0, 1.0_nd ) ;
  auto const r7 = bessel_j( 0, 10.0_nd ) ;
  
  //calculated using wolfram alpha (
  auto const r3s_wa = 0.9999999999999999750000000000000001562499999999999996 ;
  auto const r2s_wa = 0.999999999999997500000000000001562499999999999565972 ;
  auto const r1s_wa = 0.999999999999750000000000015624999999999565972222222 ;
  auto const r0_wa = 1.0 ;
  
  auto const r1_wa = 0.999999999975000000000156249999999565972222222900391 ;
  auto const r2_wa = 0.9999999975000000015624999995659722222900390624932183 ;
  auto const r3_wa = 0.9999997500000156249995659722290039061821831601931724 ;

  auto const r4_wa = 0.9999750001562495659729003899468320681722616483512528 ;
  auto const r5_wa = 0.9975015620660400322812868984747920848320082326843663 ;
  auto const r6_wa = 0.7651976865579665514497175261026632209092742897553252 ;
  auto const r7_wa = -0.24593576445134833519776086248532875382960007282656 ;

  BOOST_CHECK_CLOSE( r3s_wa , r3s.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r2s_wa , r2s.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r1s_wa , r1s.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r0_wa , r0.value(), 1e-13 );

  BOOST_CHECK_CLOSE( r1_wa , r1.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r2_wa , r2.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r3_wa , r3.value(), 1e-13 );
  
  BOOST_CHECK_CLOSE( r4_wa , r4.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r5_wa , r5.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r6_wa , r6.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r7_wa , r7.value(), 1e-13 );
}

BOOST_AUTO_TEST_CASE( bessel_1_small_test_range )
{
  auto const r0 = bessel_j( 1, 0.0_nd ) ;

  auto const r3s = bessel_j( 1, 1e-8_nd ) ;
  auto const r2s = bessel_j( 1, 1e-7_nd ) ;
  auto const r1s = bessel_j( 1, 1e-6_nd ) ;
  
  auto const r1 = bessel_j( 1, 0.00001_nd ) ;
  auto const r2 = bessel_j( 1, 0.0001_nd ) ;
  auto const r3 = bessel_j( 1, 0.001_nd ) ;

  auto const r4 = bessel_j( 1, 0.01_nd ) ;
  auto const r5 = bessel_j( 1, 0.1_nd ) ;
  auto const r6 = bessel_j( 1, 1.0_nd ) ;
  
  auto const r7 = bessel_j( 1, 10.0_nd ) ;
  auto const r8 = bessel_j( 1, 100.0_nd ) ;
  auto const r9 = bessel_j( 1, 1000.0_nd ) ;
  
  //calculated using wolfram alpha (
  auto const r0_wa = 0.0 ;

  auto const r3s_wa = 4.9999999999999999375000000000000002604166666666e-9 ;
  auto const r2s_wa = 4.9999999999999937500000000000026041666666666661e-8 ;
  auto const r1s_wa = 4.9999999999993750000000000260416666666661241319e-7 ;
  
  auto const r1_wa = 4.9999999999375000000002604166666661241319444451e-6 ;
  auto const r2_wa = 0.0000499999999375000000260416666612413194451226128471 ;
  auto const r3_wa = 0.0004999999375000026041666124131951226128415708188993 ;

  auto const r4_wa = 0.0049999375002604161241326226122820822229669808320758 ;
  auto const r5_wa = 0.0499375260362419975563365524378064840585613541415665 ;
  auto const r6_wa = 0.4400505857449335159596822037189149131273723019927652 ;
  
  auto const r7_wa = 0.0434727461688614366697487680258592883062728671185942 ;
  auto const r8_wa = -0.07714535201411215803268549492723447021161166709924 ;
  auto const r9_wa = 0.0047283119070895239175760719012169162854180242020596 ;

  BOOST_CHECK_CLOSE( r3s_wa , r3s.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r2s_wa , r2s.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r1s_wa , r1s.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r0_wa , r0.value(), 1e-13 );

  BOOST_CHECK_CLOSE( r1_wa , r1.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r2_wa , r2.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r3_wa , r3.value(), 1e-13 );
  
  BOOST_CHECK_CLOSE( r4_wa , r4.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r5_wa , r5.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r6_wa , r6.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r7_wa , r7.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r8_wa , r8.value(), 1e-13 );
  BOOST_CHECK_CLOSE( r9_wa , r9.value(), 1e-13 );

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
