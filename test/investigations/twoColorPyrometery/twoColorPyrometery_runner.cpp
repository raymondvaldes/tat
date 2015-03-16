//
//  twoColorPyrometery.cpp
//  tat-test
//
//  Created by Raymond Valdes on 1/9/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB

#include <iostream>

#include <boost/test/unit_test.hpp>


#include "investigations/main-app.h"
#include "algorithm/vector/vector2cstringArray.h"

using std::vector;
using std::string;

using investigations::main_app;
using algorithm::vector::string2charPtr;

BOOST_AUTO_TEST_SUITE( investigations )

BOOST_AUTO_TEST_SUITE( twoColorPyrometery )

BOOST_AUTO_TEST_CASE( startup ) {
  
  auto const myArguments = vector<string>
  {
    "/tmp/tat-app.dst/Users/raymondvaldes/usr/bin/tat-app",
    "--run",            "/Users/raymondvaldes/Dropbox/investigations/2color/graphite",
    "--sample",         "527F",
    "--investigation",  "twoColorPyrometery"
  };
  
  vector<char const *> vec2 = string2charPtr( myArguments );

  main_app( vec2.size() , vec2.data() );
}

BOOST_AUTO_TEST_SUITE_END() // twColorPyrometery

BOOST_AUTO_TEST_SUITE_END() // investigations
