//
//  converging_series.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


//#include <vector>
//#include "units.h"
//#include "math/sum/converging_series.h"
//using namespace units;
//using std::vector;
//
//BOOST_AUTO_TEST_SUITE( math )
//BOOST_AUTO_TEST_SUITE( sum )
//
//BOOST_AUTO_TEST_CASE( converging_series_test )
//{
//  auto const list = vector<double>({ 5,2.5,1.25,.01, .01, 0,0,0,0 });
//  auto const tol = .001;
//  
//  auto const sum_func = [ &list ]( size_t const i )
//  noexcept -> double
//  {
//    return list[i];
//  };
//  
//  auto const total = math::sum::converging_series(sum_func, tol);
//  
//  BOOST_CHECK_CLOSE_FRACTION( total, 8.77 , 1e-12 );
//  
//}
//
//
//BOOST_AUTO_TEST_SUITE_END()
//BOOST_AUTO_TEST_SUITE_END()
