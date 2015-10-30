//
//  setup.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/17/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_MODULE tat_testing
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <boost/test/unit_test.hpp>
using boost::unit_test::unit_test_main;

// entry point:
int main(int argc, char* argv[], char* envp[])
{
  return unit_test_main( &init_unit_test, argc, argv );
}