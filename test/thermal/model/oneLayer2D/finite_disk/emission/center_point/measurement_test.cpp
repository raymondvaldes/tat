//
//  measurement_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/21/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "thermal/model/oneLayer2D/finite_disk/emission/centered_point/measurement.hpp"
using thermal::model::oneLayer2D::finite_disk::disk::emission::centered_point::measurement;

#include "units.h"
using namespace units;

BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( model )
BOOST_AUTO_TEST_SUITE( oneLayer2D )
BOOST_AUTO_TEST_SUITE( finite_disk )
BOOST_AUTO_TEST_SUITE( centered_point )


BOOST_AUTO_TEST_CASE( matlab_check_first_n_phases )
{
  auto const m = 0.5_nd;
  auto const s = 2.2_nd;
  auto const w = 0.64_nd;
  auto const Bi1 = 0.1_nd;
  auto const Bi2 = 0.1_nd;
  auto const l = 1.1_nd;
  
  auto const phase_l = [=]( auto const l ) noexcept{
    auto const p = measurement( m, s, w, Bi1, Bi2, l );
    auto const phase = p.phase();
    return phase.value();
  };

  auto const tol = 1e-14;
  auto const p0 = 0.785325457862855;
  auto const p1 = 0.784491698246938;
  auto const p2 = 0.758721431337157;
  auto const p3 = 0.637695345750720;
  auto const p4 = 0.0315291784827386;
  auto const p5 = 0.000315529475772196;
  
  BOOST_CHECK_CLOSE_FRACTION( phase_l( .001_nd ), p0, tol );
  BOOST_CHECK_CLOSE_FRACTION( phase_l( .01_nd ), p1, tol );
  BOOST_CHECK_CLOSE_FRACTION( phase_l( .1_nd ), p2, tol );
  BOOST_CHECK_CLOSE_FRACTION( phase_l( 1._nd ), p3, tol );
  BOOST_CHECK_CLOSE_FRACTION( phase_l( 10._nd ), p4, tol );
  BOOST_CHECK_CLOSE_FRACTION( phase_l( 100._nd ), p5, tol );

}

BOOST_AUTO_TEST_CASE( matlab_check_first_n_amplitudes )
{
  auto const m = 1.0_nd;
  auto const s = 2.2_nd;
  auto const w = 0.64_nd;
  auto const Bi1 = 0.1_nd;
  auto const Bi2 = 0.1_nd;
  auto const l = 1.1_nd;
  
  auto const amplitude_l = [=]( auto const l ) noexcept{
    auto const p = measurement( m, s, w, Bi1, Bi2, l );
    auto const amplitude = p.amplitude();
    return amplitude.value();
  };
  
  auto const tol = 1e-14;
  auto const p0 = 0.000318287398743218;
  auto const p1 = 0.00318084829752384;
  auto const p2 = 0.0315662383326774;
  auto const p3 = 0.213426542297527;
  auto const p4 = 0.601604939479067;
  auto const p5 = 0.602088248617059;
  
  BOOST_CHECK_CLOSE_FRACTION( amplitude_l( .001_nd ), p0, tol );
  BOOST_CHECK_CLOSE_FRACTION( amplitude_l( .01_nd ), p1, tol );
  BOOST_CHECK_CLOSE_FRACTION( amplitude_l( .1_nd ), p2, tol );
  BOOST_CHECK_CLOSE_FRACTION( amplitude_l( 1._nd ), p3, tol );
  BOOST_CHECK_CLOSE_FRACTION( amplitude_l( 10._nd ), p4, tol );
  BOOST_CHECK_CLOSE_FRACTION( amplitude_l( 100._nd ), p5, tol );

}


BOOST_AUTO_TEST_CASE( matlab_check_first_n_phases_big_R )
{
  auto const m = 0.5_nd;
  auto const s = 2.2_nd;
  auto const w = 0.64_nd;
  auto const Bi1 = 0.1_nd;
  auto const Bi2 = 0.1_nd;
  auto const l = 1.1_nd;
  
  auto const phase_l = [=]( auto const s ) noexcept{
    auto const p = measurement( m, s, w, Bi1, Bi2, l );
    auto const phase = p.phase();
    return phase.value();
  };
  
//  phase_l( 500.00 );


}

BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
BOOST_AUTO_TEST_SUITE_END()  // suite
