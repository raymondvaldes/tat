//
//  columnData.cpp
//  tat
//
//  Created by Raymond Valdes on 1/5/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <boost/assert.hpp>

#include "tools/interface/import/columnData.h"

#include "algorithm/string/starts_with.h"
#include "algorithm/stream/resetInputBeginning.h"
#include "algorithm/stream/eof.h"
#include "algorithm/stream/getline.h"
#include "algorithm/stream/validateOpenStream.h"
#include "algorithm/string/split.h"
#include "algorithm/string/trim.h"
#include "algorithm/string/trim_all.h"

namespace tools {
namespace interface {
namespace import {

  columnData::columnData( const std::string& filePathIn )
  : my_ifstream( filePathIn, std::ifstream::in )
  {
    using algorithm::stream::validateOpenFile ;
    validateOpenFile( my_ifstream ) ;
    
    processData();
  }
  
  auto columnData::processData( void ) -> void
  {
    extractDataLines();
  
    const auto poorDataIntegrity = !verifyDataIntegrity() ;
    const auto throwException = poorDataIntegrity ;
    
    if( throwException ) {
      using std::invalid_argument;
      throw invalid_argument( "Input data not in matrix form." ) ;
    }
  }
  
  auto columnData::extractDataLines( void ) noexcept -> void
  {
    using algorithm::stream::not_eof;
    while( not_eof( my_ifstream ) ) {
      saveDataLine();
    }
  }

  auto columnData::saveDataLine( void ) noexcept -> void
  {
    using algorithm::stream::getline;
    auto currentLine = getline( my_ifstream ) ;
    
    using algorithm::string::trim;
    trim( currentLine );

    using algorithm::string::starts_with_not;
    const auto NotcommentLine = starts_with_not( currentLine, IgnoreCharacter );
    const auto NotBlankLine = !currentLine.empty();
    
    if( NotcommentLine && NotBlankLine ) {
      cleanFileStream << currentLine << "\n" ;
    }
  }

  auto columnData::updateCommentSymbol( const std::string& Symbol )
    noexcept -> void
  {
    IgnoreCharacter = Symbol;
    processData();
  }
  
  auto columnData::verifyDataIntegrity(void) noexcept -> bool
  {
    size_t nColumns = 0;
    size_t nRows = 0;
    size_t nElements = 0;
    resetDataVectors();
    
    using algorithm::stream::seekBeginning;
    seekBeginning( cleanFileStream ) ;
    
    using algorithm::stream::not_eof;

    while( not_eof( cleanFileStream ) )
    {
      using algorithm::stream::getline;
      const auto myLine = getline( cleanFileStream ) ;
      
      if( !myLine.empty() ) {
        nRows++;

        using algorithm::string::trim_fill_copy;
        auto myLineTrimmed = trim_fill_copy( myLine, "\t");

        using algorithm::string::split;
        auto myRowElements = split( myLineTrimmed, "\t" ) ;
        
        rows.push_back( myRowElements );

        nElements += myRowElements.size();
        nColumns = myRowElements.size();
      }
    }
    rows.shrink_to_fit() ;

    const auto matrixForm = ( nElements == nRows * nColumns ) ;
    
    if( matrixForm )
    {
      columns.resize( nColumns ) ;
      for( auto& column: columns) {
        column.resize( nRows ) ;
      }
      
      size_t i = 0 ;
      size_t j = 0 ;
      
      for( const auto& row: rows) {
        for( const auto& Element: row ) {
          columns[i][j] = Element;
          i++;
        }
        i = 0;
        j++;
      }
      
    }

    return matrixForm;
  }
  
  auto columnData::resetDataVectors(void) noexcept -> void
  {
    rows.clear();
    for( auto&row: rows )
      row.clear();
    
    columns.clear();
    for( auto&column: columns )
      column.clear();
  }
  
  auto columnData::getColumn( const size_t columnNumber )
    noexcept -> std::vector<std::string>
  {
    BOOST_ASSERT( columnNumber > 0 );

    return columns[ columnNumber - 1 ] ;
  }
  
  auto columnData::getRow( const size_t rowNumber )
    noexcept -> std::vector<std::string>
  {
    BOOST_ASSERT( rowNumber > 0 );
    return rows[ rowNumber - 1 ] ;
  }
  
  
  auto columnData::getElement(
    const size_t rowNumber, const size_t columnNumber )
  noexcept -> std::string
  {
    return rows[ rowNumber - 1 ][ columnNumber - 1] ;
  }
      
}}}