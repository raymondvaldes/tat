//
//  split_T.cpp
//  tat-test
//
//  Created by Raymond Valdes on 6/23/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "algorithm/string/split.h"
using algorithm::string::split;
typedef std::vector<std::string> vector_strings;

BOOST_AUTO_TEST_SUITE( algorithm )

struct AccessStrings {
  const std::string singleword = "pizza" ;
  const std::string directory = "/home/user/file/stuff.cpp" ;
  const std::string add_words = "alpha+bravo+charlie+delta" ;
  const std::string spaced_words = "one two three four five" ;
  const std::string numbers_delimiters = "0::0::0::0::0::::" ;
  
  const std::string plus = "/+" ;
  const std::string slash = "//" ;
  const std::string space = " " ;
  const std::string doublecolon = "::" ;
};

BOOST_FIXTURE_TEST_SUITE( string, AccessStrings )


BOOST_AUTO_TEST_CASE( split_no_delims ) {
  vector_strings out = split( singleword, slash  ) ;
  
  BOOST_CHECK_EQUAL( out.size() , 1 ) ;
  BOOST_CHECK_EQUAL( out.front() , singleword ) ;
}

BOOST_AUTO_TEST_CASE( split_directory ) {
  vector_strings out = split( directory, slash  ) ;
  
  BOOST_CHECK_EQUAL( out.size() , 5 ) ;
  BOOST_CHECK_EQUAL( out.front() , "" ) ;
}

BOOST_AUTO_TEST_CASE( split_string_with_plus ) {
  vector_strings out = split( add_words, plus ) ;
  
  BOOST_CHECK_EQUAL( out.size() , 4 ) ;
  BOOST_CHECK_EQUAL( out.front() , "alpha" ) ;
}

BOOST_AUTO_TEST_CASE( split_with_space ) {
  vector_strings out = split( spaced_words, space ) ;
  
  BOOST_CHECK_EQUAL( out.size() , 5 ) ;
  BOOST_CHECK_EQUAL( out.front() , "one" ) ;
}

BOOST_AUTO_TEST_CASE( split_numbers ) {
  vector_strings out = split( numbers_delimiters , doublecolon ) ;
  
  BOOST_CHECK_EQUAL( out.size() , 6 ) ;
  BOOST_CHECK_EQUAL( out.front() , "0" ) ;
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
