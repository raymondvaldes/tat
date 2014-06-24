//
//  starts_with.cpp
//  tat-test
//
//  Created by Raymond Valdes on 6/24/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "algorithm/string/starts_with.h"
using algorithm::string::starts_with;

BOOST_AUTO_TEST_SUITE( algorithm )

struct Access {
  const std::string singleword = "pizza" ;
  const std::string directory = "/home/user/file/stuff.cpp" ;
  const std::string add_words = "alpha+bravo+charlie+delta" ;
  const std::string spaced_words = " one two three four five" ;
  const std::string numbers_delimiters = "0::0::0::0::0::::" ;
};

BOOST_FIXTURE_TEST_SUITE( string_starts_with, Access )

BOOST_AUTO_TEST_CASE( string_starts_with ) {

  const bool pass = starts_with( singleword, "pi" ) ;
  BOOST_CHECK( pass ) ;
}

BOOST_AUTO_TEST_CASE( numbers_delimiters ) {

  const bool fail = starts_with( singleword, "::" ) ;
  BOOST_CHECK( !fail ) ;
}

BOOST_AUTO_TEST_CASE( string_starts_with_space) {

  const bool pass = starts_with( spaced_words, " one two " ) ;
  BOOST_CHECK( pass ) ;
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
