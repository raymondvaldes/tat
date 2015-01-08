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

  BOOST_CHECK_NO_THROW( columnData(
  "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt" ) ) ;
}


BOOST_AUTO_TEST_CASE( read_rows ) {

  const auto myInput = "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt";
  columnData myData( myInput ) ;

  const auto firstRow = myData.getRow( 5 ) ;

}

BOOST_AUTO_TEST_CASE( read_columns ) {

  const auto myInput = "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt";
  columnData myData( myInput ) ;

  const auto firstColumns = myData.getColumn( 2 ) ;

}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
