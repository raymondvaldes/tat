//
//  measurement_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/21/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "thermal/model/oneLayer2D/finite_disk/seperation_of_variables/lambda_generator.hpp"
#include "thermal/model/oneLayer2D/finite_disk/emission/centered_detector_with_view/measurement.hpp"

using thermal::model::oneLayer2D::finite_disk::seperation_of_variables::Lambda_generator;
using thermal::model::oneLayer2D::finite_disk::disk::emission::centered_with_view::measurement;

#include "units.h"
using namespace units;

BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( oneLayer2D )
BOOST_AUTO_TEST_SUITE( finite_disk )
BOOST_AUTO_TEST_SUITE( centered_detector_with_view )

BOOST_AUTO_TEST_CASE( matlab_check_first_n_phases_big_R )
{
  auto const m = 0.5_nd;
  auto const s = 2.2_nd;
  auto const w = 0.64_nd;
  auto const Bi1 = 0.1_nd;
  auto const Bi2 = 0.1_nd;
  auto const l = 1.1_nd;
  
  auto const phase_l = [=]( auto const r_e ) noexcept{
    auto const p = measurement( m, r_e, s, w, Bi1, Bi2, l );
    auto const phase = p.phase();
    return phase.value();
  };
  
  phase_l( 5._nd );


}


BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
