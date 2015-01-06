//
//  columnData.cpp
//  tat-test
//
//  Created by Raymond Valdes on 1/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>
#include <string>
#include <stdexcept>
#include <vector>
#include "tools/interface/import/columnData.h"


BOOST_AUTO_TEST_SUITE( tools )
BOOST_AUTO_TEST_SUITE( interface )
BOOST_AUTO_TEST_SUITE( import )

  using tools::interface::import::columnData;


BOOST_AUTO_TEST_CASE( constructor_fails) {

  BOOST_CHECK_THROW( columnData( "mydummy.txt" ) , std::invalid_argument ) ;
  
  
}

BOOST_AUTO_TEST_CASE( constructor_opens ) {

  const std::string myInput = "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt";

  BOOST_CHECK_NO_THROW( columnData(
  "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt" ) ) ;
  
  
  columnData myData(myInput);
  
//  BOOST_CHECK( myData.file_is_open() ) ;
//  BOOST_CHECK( !myData.file_is_closed() ) ;
}


BOOST_AUTO_TEST_CASE( read_columns ) {

  const std::string myInput = "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt";
  columnData myData( myInput ) ;

  using std::vector;
  using std::string;
  
  vector< string > firstColumn(0);
  
  firstColumn =
   myData.getColumn<string>( 1 ) ;
  
  
  
  std::cout << "\n\n" ;
  std::cout << "this vector is " ;
  std::cout <<  (firstColumn.empty() ? "empty ": "not empty") << "\n" ;
  
  for( auto& val : firstColumn )
    std::cout << val << "\n";
}





BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
