//
//  quantityTodouble.cpp
//  tat-test
//
//  Created by Raymond Valdes_New on 2/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "algorithm/vector/quantityTodouble.h"
#include "algorithm/vector/doubleToQuantity.h"

BOOST_AUTO_TEST_SUITE( algorithm )

BOOST_AUTO_TEST_SUITE( vector )


BOOST_AUTO_TEST_CASE( quantityTodoubleTest ) {

  auto const myValue = 2.0 * units::si::meters;
  
  std::vector< units::quantity<units::si::length >> myVector(5) ;
  
  std::fill( std::begin( myVector ), std::end( myVector ), myValue ) ;
  

  using algorithm::vector::quantityTodouble;
  const auto myVectorDouble = quantityTodouble( myVector );

  constexpr auto tol = 0.0000001;
  
  for( auto i = 0 ; i < myVector.size(); ++i )
  {
    BOOST_WARN_CLOSE( myVectorDouble[i], myVector[i].value() , tol );
  }

}



BOOST_AUTO_TEST_CASE( doubleToquantityTest ) {
  using std::vector;
  using std::fill;
  using std::begin;
  using std::end;


  auto const myValue = 2.0;
  
  vector< double >  myVector(5) ;
  fill( begin( myVector ), end( myVector ), myValue ) ;
  

  using algorithm::vector::doubleToQuantity;
  const auto myVectorDouble = doubleToQuantity< units::si::length >( myVector , units::si::meter);

  constexpr auto tol = 0.0000001;
  
  for( auto i = 0 ; i < myVector.size(); ++i )
  {
    BOOST_WARN_CLOSE( myVectorDouble[i].value(), myVector[i] , tol );
  }

}



BOOST_AUTO_TEST_SUITE_END() // end vector

BOOST_AUTO_TEST_SUITE_END() // end algorithm