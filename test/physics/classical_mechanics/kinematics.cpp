//
//  kinematics.cpp
//  tat-test
//
//  Created by Raymond Valdes on 6/24/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include "physics/classical_mechanics/kinematics.h"
using physics::classical_mechanics::period_to_angularFrequency;
using physics::classical_mechanics::angularFrequency_to_period;

BOOST_AUTO_TEST_SUITE( physics )


class rotational_data {
public:

  class rotational_rate {
  public:
    const double period;
    const double angularFreq;
    rotational_rate( const double period_in, const double angularFreq_in )
      : period( period_in), angularFreq( angularFreq_in )  {};
  };

  const rotational_rate true1 = rotational_rate( 6.2831853071795864  , 1 ) ;
  const rotational_rate true2 = rotational_rate( 0.0172024238389584 , 365.25 ) ;
  const rotational_rate true3 = rotational_rate( 1, 6.2831853071795864 ) ;

  const double tol = 1e-12;
  
};

typedef rotational_data::rotational_rate rate;
rate calc_dependencies( const rate input )
{
  const double period_calc = angularFrequency_to_period( input.angularFreq ) ;
  const double angularFreq_calc = period_to_angularFrequency( input.period ) ;

  const rate output_calc( period_calc, angularFreq_calc );

  return output_calc;
};



BOOST_FIXTURE_TEST_SUITE( classica_mechanics, rotational_data )


BOOST_AUTO_TEST_CASE( angularFreq_to_period ) {

  const rate calc_val1 = calc_dependencies( true1 ) ;
  BOOST_CHECK_CLOSE( calc_val1.period, true1.period, tol ) ;
  BOOST_CHECK_CLOSE( calc_val1.angularFreq, true1.angularFreq, tol ) ;

  const rate calc_val2 = calc_dependencies( true2 ) ;
  BOOST_CHECK_CLOSE( calc_val2.period, true2.period, tol ) ;
  BOOST_CHECK_CLOSE( calc_val2.angularFreq, true2.angularFreq, tol ) ;

  const rate calc_val3 = calc_dependencies( true3 ) ;
  BOOST_CHECK_CLOSE( calc_val3.period, true3.period, tol ) ;
  BOOST_CHECK_CLOSE( calc_val3.angularFreq, true3.angularFreq, tol ) ;


}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()