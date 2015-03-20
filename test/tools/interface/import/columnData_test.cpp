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

  auto const myInput =
  "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt";
  columnData myData( myInput ) ;

  auto const firstRow = myData.getRow( 1 ) ;
  auto const lastRow = myData.getRow( 5 ) ;
  
  auto const pass_1 = firstRow == vector_strings{"3", "1"} ;
  auto const fail_1 = firstRow != vector_strings{"3", "error"} ;
  
  auto const pass_2 = lastRow == vector_strings{"the", "end"} ;
  auto const fail_2 = lastRow != vector_strings{"error", "end"} ;
  
  BOOST_CHECK( pass_1 );
  BOOST_CHECK( pass_2 );
  BOOST_CHECK( fail_1 );
  BOOST_CHECK( fail_2 );

}

BOOST_AUTO_TEST_CASE( getColumn ) {
  typedef std::vector<std::string> vector_strings;

  auto const myInput =
  "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt";
  columnData myData( myInput ) ;

  auto const extractedColumn = myData.getColumn( 2 ) ;

  auto const pass = extractedColumn == vector_strings{ "1","1","9","6", "end" } ;
  auto const fail = extractedColumn != vector_strings{ "1","1","9","6", "error!!" } ;
  
  BOOST_CHECK( pass );
  BOOST_CHECK( fail );
}


BOOST_AUTO_TEST_CASE( getDataFile ) {
  typedef std::vector<std::string> vector_strings;
  auto const myInput =
  "/Users/raymondvaldes/code/tat/test/tools/interface/import/graphite_400F_4.4_2.82843_0.dat";
  
  columnData myData( myInput ) ;

  auto const extractedColumn = myData.getColumn( 1 ) ;
}

BOOST_AUTO_TEST_CASE( getElement ) {

  auto const myInput =
  "/Users/raymondvaldes/code/tat/test/tools/interface/import/data.txt";
  columnData myData( myInput ) ;
  
  auto const pullFirst = myData.getElement( 1 , 1 ) ;
  auto const pullLast = myData.getElement( 5 , 2 ) ;

  auto const pass_1 = pullFirst == std::string{ "3" } ;
  auto const pass_2 = pullLast == std::string{ "end" } ;
  
  BOOST_CHECK( pass_1 ) ;
  BOOST_CHECK( pass_2 ) ;
}

BOOST_AUTO_TEST_SUITE_END() // import

BOOST_AUTO_TEST_SUITE_END() // interface

BOOST_AUTO_TEST_SUITE_END() // tools
