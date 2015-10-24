//
//  complex_lambda_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/20/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "thermal/model/oneLayer2D/finite_disk/seperation_of_variables/complex_lambda.h"
#include "units.h"
#include "thermal/model/oneLayer2D/finite_disk/seperation_of_variables/lambda_generator.hpp"

using thermal::model::oneLayer2D::finite_disk::seperation_of_variables::Lambda_generator;
using thermal::model::oneLayer2D::finite_disk::seperation_of_variables::complex_lambda;
using namespace units;
using namespace std::complex_literals;

BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( oneLayer2D )
BOOST_AUTO_TEST_SUITE( finite_disk )
BOOST_AUTO_TEST_SUITE( seperation_of_variables )

BOOST_AUTO_TEST_CASE( complex_lambda_function )
{
  auto const lambda = 1.25_nd;
  auto const l = 0.5_nd;


  auto const l_cmplx = complex_lambda( lambda , l  );
  auto const cmplx = l_cmplx.value();

  auto const real_actual = 1.71126;
  auto const imaginary_actual = 1.16873;
  auto const tol = 1e-5;

  BOOST_CHECK_CLOSE_FRACTION( cmplx.real(), real_actual, tol);
  BOOST_CHECK_CLOSE_FRACTION( cmplx.imag(), imaginary_actual, tol);
  
}

BOOST_AUTO_TEST_CASE( complex_lambda_test_matlab )
{
  auto const a0 = 0.677129180510131 + 0.610257469903389i;
  auto const a1 = 1.78269635525709 + 0.231796704625154i;
  auto const a2 = 3.20571330622009 + 0.128902088559849i;
  auto const a3 = 4.63497874315263 + 0.0891531899917195i;
  auto const a4 = 6.06410658081787 + 0.0681424600621278i;
  auto const a5 = 7.49292156730916 + 0.0551484673613451i;
  auto const a6 = 8.92151580273721 + 0.0463175932916116i;
  auto const a7 = 10.3499624938250 + 0.0399250857906397i;
  auto const a8 = 11.7783083852197 + 0.0350834030644341i;
  auto const a9 = 13.2065831470175 + 0.0312891787297146i;
  auto const a10 = 14.6348061326836 + 0.0282356415759431i;

  auto const s = 2.2_nd;
  auto const bi2 = 0.1_nd;
  auto const l = 1.1_nd;
  
  auto const g = Lambda_generator( s, bi2, l );
  
  auto const n = 10;
  g.real_lambda_at( n );
  
  auto const tol = 1e-12;
  auto const complex_lambda = [&g]( auto const i)
  {
    auto const cmplx_lambda = g.complex_lambda_at(i).value();
    return cmplx_lambda;
  };
  
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 0 ).real(), a0.real(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 1 ).real(), a1.real(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 2 ).real(), a2.real(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 3 ).real(), a3.real(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 4 ).real(), a4.real(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 5 ).real(), a5.real(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 6 ).real(), a6.real(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 7 ).real(), a7.real(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 8 ).real(), a8.real(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 9 ).real(), a9.real(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 10 ).real(), a10.real(), tol);

  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 0 ).imag(), a0.imag(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 1 ).imag(), a1.imag(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 2 ).imag(), a2.imag(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 3 ).imag(), a3.imag(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 4 ).imag(), a4.imag(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 5 ).imag(), a5.imag(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 6 ).imag(), a6.imag(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 7 ).imag(), a7.imag(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 8 ).imag(), a8.imag(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 9 ).imag(), a9.imag(), tol);
  BOOST_CHECK_CLOSE_FRACTION( complex_lambda( 10 ).imag(), a10.imag(), tol);

}



BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite