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


BOOST_AUTO_TEST_SUITE( investigations )
BOOST_AUTO_TEST_SUITE( twoColorPyrometery )


BOOST_AUTO_TEST_CASE( startup ) {
  
  std::vector<std::string> myArguments = {
    "/tmp/tat-app.dst/Users/raymondvaldes/usr/bin/tat-app",
    "--run",            "/Users/raymondvaldes/Dropbox/investigations/2color",
    "--sample",         "TBC",
    "--investigation",  "twoColorPyrometery"
       };
  using algorithm::vector::vector2cstringArray;
  std::vector<char const *> vec2 = vector2cstringArray(myArguments);

  using investigations::main_app;
  main_app( vec2.size() , vec2.data() ) ;

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()