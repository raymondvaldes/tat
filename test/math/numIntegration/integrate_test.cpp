//
//  integrate_test.cpp
//  tat-test
//
//  Created by Raymond Valdes on 3/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>

#include "math/numIntegration/integrate.h"
#include "units.h"

using namespace units;
using std::vector;
using math::numIntegration::integrate;

//#include <boost/numeric/odeint.hpp>
//#include <boost/numeric/odeint/algebra/fusion_algebra.hpp>
//
//#include <boost/units/systems/si/length.hpp>
//#include <boost/units/systems/si/time.hpp>
//#include <boost/units/systems/si/velocity.hpp>
//#include <boost/units/systems/si/acceleration.hpp>
//#include <boost/units/systems/si/io.hpp>
//
//#include <boost/fusion/container.hpp>
//
//using namespace std;
//using namespace boost::numeric::odeint;
//namespace fusion = boost::fusion;
//namespace units = boost::units;
//namespace si = boost::units::si;
//
//
//typedef units::quantity< si::time , double > time_type;
//typedef units::quantity< si::length , double > length_type;
//typedef units::quantity< si::velocity , double > velocity_type;
//typedef units::quantity< si::acceleration , double > acceleration_type;
//typedef units::quantity< si::frequency , double > frequency_type;
//
//typedef fusion::vector< length_type , velocity_type > state_type;
//typedef fusion::vector< velocity_type , acceleration_type > deriv_type;
//#include "../test/math/numIntegration/integration_boost_units.h"



BOOST_AUTO_TEST_SUITE( math )
BOOST_AUTO_TEST_SUITE( numIntegrate )

//BOOST_AUTO_TEST_CASE( integrate_test_1 )
//{
//
////  //[ units_define_stepper
////  typedef runge_kutta_dopri5< state_type , double , deriv_type , time_type , fusion_algebra > stepper_type;
////
////  state_type x( 1.0 * si::meter , 0.0 * si::meter_per_second );
////
////  integrate_const( make_dense_output( 1.0e-6 , 1.0e-6 , stepper_type() ) , oscillator( 2.0 * si::hertz ) , x , 0.0 * si::second , 100.0 * si::second , 0.1 * si::second , streaming_observer( cout ) );
////  //]
//
//
//
//}

BOOST_AUTO_TEST_CASE( integrate_test_2 )
{
  //func_type const & func,
  
  auto const x0 = double(0.);
  auto const x1 = double( 0.5 );
  auto const dx_intial_step = double( 0.1 );

  // given integrate f(x) from a to b.  Must satisfy F(a) = 0;
  auto const f_x0 = vector< double > ( { 0 } );
  auto const func = []
  (
    vector< double > const & y,
    vector< double > & dy,
    double const x
  ) noexcept -> void
  {
    dy[0] = x ;
  };

  auto const area_under_curve =
  math::numIntegration::integrate( func, f_x0, x0, x1, dx_intial_step );
  
  BOOST_CHECK_CLOSE( area_under_curve, 0.125 , 1e-10);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()