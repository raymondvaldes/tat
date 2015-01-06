//
//  columnData.cpp
//  tat
//
//  Created by Raymond Valdes on 1/5/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "tools/interface/import/columnData.h"

namespace tools {
namespace interface {
namespace import {

  auto columnData::validateOpenFile( void ) -> void {
    const bool throwException = file_is_closed( ) ;
    
    if( throwException ) {
      using std::invalid_argument;
      throw invalid_argument( "no file found" ) ;
    }
  }


  columnData::columnData( const std::string& filePathIn )
  : inputFileStream( filePathIn, std::ifstream::in )
  {
    validateOpenFile();
    eliminateCommentLines();
  }

  auto columnData::saveDataLine( void ) noexcept -> void
  {
    using std::string;
    const string currentLine = readLine() ;
    
    using algorithm::string::starts_with_not;
    const bool NotcommentLine = starts_with_not( currentLine, defaultIgnoreCharacter ) ;
    
    if( NotcommentLine ) {
      cleanFileStream << currentLine;
    }
  }

  auto columnData::eliminateCommentLines( void ) noexcept -> void
  {
    while( NotEOF() ) {
      saveDataLine();
    }
  }

  auto columnData::endOfFile(void) noexcept -> bool
  {
    return inputFileStream.eof();
  }

  auto columnData::NotEOF(void) noexcept -> bool
  {
    return !endOfFile();
  }

  auto columnData::updateCommentSymbol( const std::string& Symbol ) noexcept -> void
  {
    defaultIgnoreCharacter = Symbol;
    eliminateCommentLines();
  }

  auto columnData::file_is_open() const noexcept -> bool
  {
    return inputFileStream.is_open();
  }

  auto columnData::file_is_closed() const noexcept -> bool
  {
    return !file_is_open();
  }

  auto columnData::readLine() noexcept -> std::string
  {
    using std::string;
    using std::getline;

    string getsThisLine ;
    getline( inputFileStream , getsThisLine ) ;
    
    return getsThisLine ;
  }

  auto columnData::rejectLine( const std::string& line ) noexcept -> bool
  {
    return line.empty();
  }


  auto columnData::changeIgnoreLines( const std::string& myChar ) noexcept -> void
  {
    defaultIgnoreCharacter = myChar ;
    
    using algorithm::stream::resetToBeginnging;
    using std::ifstream;
    
    resetToBeginnging<ifstream>( inputFileStream ) ;
    
    eliminateCommentLines();
  }
  
  

  auto columnData::NumberOfColumns(void) noexcept -> size_t
  {
    
  
    return 0;
  }
  
  auto columnData::NumberofRows(void) noexcept -> size_t 
  {
    return 0;
  }
      
      
      
  
}}}