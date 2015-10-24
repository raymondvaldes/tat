//
//  lambda_generator.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "thermal/model/oneLayer2D/finite_disk/seperation_of_variables/lambda_generator.hpp"
#include "units.h"

using thermal::model::oneLayer2D::finite_disk::seperation_of_variables::Lambda_generator;
using namespace units;

BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( oneLayer2D )
BOOST_AUTO_TEST_SUITE( finite_disk )
BOOST_AUTO_TEST_SUITE( seperation_of_variables )

BOOST_AUTO_TEST_CASE( constructor_test )
{
  auto const s = 1._nd;
  auto const bi = 2.5_nd;
  auto const l = 1.1_nd;
  
  BOOST_CHECK_NO_THROW( Lambda_generator( s, bi, l ) );

}


BOOST_AUTO_TEST_CASE( first_n_lambdas )
{
  auto const s = 1._nd;
  auto const bi = 10.0_nd;
  auto const l = 1.1_nd;
  
  auto const lambda_generator = Lambda_generator( s, bi, l );
  
  auto const n = 50;
  lambda_generator.real_lambda_at( n );

}

BOOST_AUTO_TEST_CASE( first_n_lambdas_zero )
{
  auto const s = 1._nd;
  auto const bi = 0.001_nd;
  auto const l = 1.1_nd;
  
  auto const lambda_generator = Lambda_generator( s, bi, l );
  
  auto const n = 50;
  lambda_generator.real_lambda_at( n );

}



BOOST_AUTO_TEST_CASE( eigenerr_check )
{
  auto const s = 2.2_nd;
  auto const bi2 = 0.1_nd;
  auto const l = 1.1_nd;
  
  auto const g = Lambda_generator( s, bi2, l );
  
  auto const lam = [s]( auto const b){ return b / s.value(); };
  
  auto const e1 = g.objective_function( lam(0) );
  auto const e2 = g.objective_function( lam(0.01) );
  auto const e3 = g.objective_function( lam(.1 ) );
  auto const e4 = g.objective_function( lam(1.0) )  ;
  auto const e5 = g.objective_function( lam(10.0 ) );
  auto const e6 = g.objective_function( lam(100. ) );

  auto const tol = 1e-12;
  
  BOOST_CHECK_CLOSE_FRACTION( e1, -0.220000000000000, tol);
  BOOST_CHECK_CLOSE_FRACTION( e2, -0.219944500659372, tol);
  BOOST_CHECK_CLOSE_FRACTION( e3, -0.214456591050905, tol);
  BOOST_CHECK_CLOSE_FRACTION( e4, 0.271707094702181, tol);
  BOOST_CHECK_CLOSE_FRACTION( e5, 0.488833329867911, tol);
  BOOST_CHECK_CLOSE_FRACTION( e6, -7.71893208847814, tol);
}


BOOST_AUTO_TEST_CASE( matlab_check_first_n )
{
  auto const s = 2.2_nd;
  auto const bi2 = 0.1_nd;
  auto const l = 1.1_nd;
  
  auto const g = Lambda_generator( s, bi2, l );
  
  auto const n = 11;
  g.real_lambda_at( n );
  
  auto const tol = 1e-12;
  auto const lambda =
    [&g]( auto const i) { return g.real_lambda_at( i ).value();};

  BOOST_CHECK_CLOSE_FRACTION( lambda( 0 ), 0.293410544332400, tol);
  BOOST_CHECK_CLOSE_FRACTION( lambda( 1 ), 1.76756232783227, tol);
  BOOST_CHECK_CLOSE_FRACTION( lambda( 2 ), 3.20312067416160, tol);
  BOOST_CHECK_CLOSE_FRACTION( lambda( 3 ), 4.63412123904749, tol);
  BOOST_CHECK_CLOSE_FRACTION( lambda( 4 ), 6.06372370978883, tol);
  BOOST_CHECK_CLOSE_FRACTION( lambda( 5 ), 7.49271861612288, tol);
  BOOST_CHECK_CLOSE_FRACTION( lambda( 6 ), 8.92139556902626, tol);
  BOOST_CHECK_CLOSE_FRACTION( lambda( 7 ), 10.3498854878259, tol);
  BOOST_CHECK_CLOSE_FRACTION( lambda( 8 ), 11.7782561345968, tol);
  BOOST_CHECK_CLOSE_FRACTION( lambda( 9 ), 13.2065460816363, tol);
  BOOST_CHECK_CLOSE_FRACTION( lambda( 10 ), 14.6347788944616, tol);

}

BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite

