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


BOOST_AUTO_TEST_CASE( constructor ) {

  BOOST_CHECK_NO_THROW( columnData(
  "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt" ) ) ;
  
  BOOST_CHECK_THROW( columnData( "mydummy.txt" ) , std::invalid_argument ) ;
  
  BOOST_CHECK_THROW(
    columnData(
    "/Users/raymondvaldes/code/tat/test/tools/interface/import/data_badForm.txt"
    ) , std::invalid_argument ) ;
  
}

BOOST_AUTO_TEST_CASE( getRow ) {
  typedef std::vector<std::string> vector_strings;

  const auto myInput = "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt";
  columnData myData( myInput ) ;

  const auto firstRow = myData.getRow( 1 ) ;
  const auto lastRow = myData.getRow( 5 ) ;
  
  const auto pass_1 = firstRow == vector_strings{"3", "1"} ;
  const auto fail_1 = firstRow != vector_strings{"3", "error"} ;
  
  const auto pass_2 = lastRow == vector_strings{"the", "end"} ;
  const auto fail_2 = lastRow != vector_strings{"error", "end"} ;
  
  BOOST_CHECK( pass_1 );
  BOOST_CHECK( pass_2 );
  BOOST_CHECK( fail_1 );
  BOOST_CHECK( fail_2 );

}

BOOST_AUTO_TEST_CASE( getColumn ) {
  typedef std::vector<std::string> vector_strings;

  const auto myInput = "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt";
  columnData myData( myInput ) ;

  const auto extractedColumn = myData.getColumn( 2 ) ;

  const auto pass = extractedColumn == vector_strings{ "1","1","9","6", "end" } ;
  const auto fail = extractedColumn != vector_strings{ "1","1","9","6", "error!!" } ;
  
  BOOST_CHECK( pass );
  BOOST_CHECK( fail );
}

BOOST_AUTO_TEST_CASE( getElement ) {

  const auto myInput =
  "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt";
  columnData myData( myInput ) ;
  
  const auto pullFirst = myData.getElement( 1 , 1 ) ;
  const auto pullLast = myData.getElement( 5 , 2 ) ;

  const auto pass_1 = pullFirst == std::string{ "3" } ;
  const auto pass_2 = pullLast == std::string{ "end" } ;
  
  BOOST_CHECK( pass_1 ) ;
  BOOST_CHECK( pass_2 ) ;
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
