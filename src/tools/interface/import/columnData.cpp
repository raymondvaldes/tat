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
#include "math/matrixAnalysis/valid.h"

using std::for_each;
using std::begin;
using std::end;
using std::invalid_argument;

namespace tools {

namespace interface {

namespace import {

  auto columnData::validateAndProcess(void) -> void
  {
    using algorithm::stream::validateOpenFile ;
    validateOpenFile( my_ifstream ) ;
    processData();
  }

  columnData::columnData( std::string const & filePathIn )
  : columnData( filePathIn, "#")
  {}

  columnData::columnData( std::string const & filePathIn,
                          std::string const & ignoreCharacterIn )
  : my_ifstream( filePathIn, std::ifstream::in ),
    IgnoreCharacter(ignoreCharacterIn)
  
  {
    validateAndProcess();
  }
  
  auto columnData::processData( void ) -> void
  {
    extract_file_to_stream();
  
    auto const poorDataIntegrity = !verifyDataIntegrity() ;
    auto const throwException = poorDataIntegrity ;
    
    if( throwException ) {
      throw invalid_argument( "Input data not in matrix form." ) ;
    }
  }
  
  auto columnData::extract_file_to_stream( void ) noexcept -> void
  {
    using algorithm::stream::not_eof;
    while( not_eof( my_ifstream ) ) {
      saveDataLine();
    }
  }

  auto columnData::saveDataLine( void ) noexcept -> void
  {
    using algorithm::stream::getline;
    using algorithm::string::trim;
    using algorithm::string::starts_with_not;
    
    auto currentLine = getline( my_ifstream ) ;

    trim( currentLine );

    auto const NotcommentLine = starts_with_not( currentLine, IgnoreCharacter );
    auto const NotBlankLine = !currentLine.empty();
    
    if( NotcommentLine && NotBlankLine ) {
      cleanFileStream << currentLine << "\n" ;
    }
  }

  auto columnData::verifyDataIntegrity(void) noexcept -> bool
  {
    using algorithm::stream::seekBeginning_of_file;
    using algorithm::stream::not_eof;
    using math::matrixAnalysis::valid;

    auto nColumns = size_t(0);
    auto nRows = size_t(0);
    auto nElements = size_t(0);
    
    const auto recordDataFromLine = [&]( auto& myLine )
    {
        using algorithm::string::trim_fill_copy;
        using algorithm::string::split;
        
        nRows++;
        auto myLineTrimmed = trim_fill_copy( myLine, "\t") ;
        auto myRowElements = split( myLineTrimmed, "\t" ) ;
        
        rows.push_back( myRowElements );

        nElements += myRowElements.size();
        nColumns = myRowElements.size();
    };

    const auto recordDataFromStream = [&]()
    {
      using algorithm::stream::getline;
      auto const currentLine = getline( cleanFileStream ) ;
      auto const line_has_content = !currentLine.empty();
      
      if( line_has_content ) {
        recordDataFromLine(currentLine);
      }
    };
    
    const auto populateDataContainer = [&](){
      columns.resize( nColumns ) ;
      
      for_each( begin( columns ), end( columns ), [=](auto& column){
        column.resize( nRows ) ;
      }  );
      
      auto i = size_t(0) ;
      auto j = size_t(0) ;
      for_each( begin( rows ), end( rows ), [&]( auto& row ){
        for_each( begin( row ), end( row ), [&]( auto& Element){
          columns[i++][j] = Element;
        }  );
        
        i = 0;
        j++;
      } );
    };
    
    clearDataVectors();
    
    seekBeginning_of_file( cleanFileStream ) ;

    while( not_eof( cleanFileStream ) ) {
      recordDataFromStream();
    }

    auto const is_validMatrix = valid( nRows, nColumns, nElements ) ;
    
    if( is_validMatrix ) {
      populateDataContainer();
    }

    return is_validMatrix;
  }
  
  auto columnData::clearDataVectors(void) noexcept -> void
  {
    rows.clear();
    for_each( begin(rows), end(rows), []( auto& row){
      row.clear();
    } );
    
    columns.clear();
    for_each( begin( columns ), end( columns ), [](auto& column){
      column.clear();
    } );
    
  }
  
  auto columnData::getColumn( size_t const columnNumber ) const
    noexcept -> std::vector<std::string>
  {
    BOOST_ASSERT( columnNumber > 0 );
    return columns[ columnNumber - 1 ] ;
  }
  
  auto columnData::getRow( size_t const rowNumber ) const
    noexcept -> std::vector<std::string>
  {
    BOOST_ASSERT( rowNumber > 0 );
    return rows[ rowNumber - 1 ] ;
  }
  
  auto columnData::getElement( size_t const rowN, size_t const columnN ) const
  noexcept -> std::string
  {
    return rows[ rowN - 1 ][ columnN - 1] ;
  }

  auto columnData::size( void ) const noexcept -> size_t
  {
    return rows.size();
  }
      
} // namespace import

} // namespace interface

} // namespace tools
