//
//  columnData.cpp
//  tat
//
//  Created by Raymond Valdes on 1/5/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "tools/interface/import/columnData.h"

#include "algorithm/string/starts_with.h"
#include "algorithm/stream/resetInputBeginning.h"
#include "algorithm/stream/eof.h"
#include "algorithm/stream/getline.h"
#include "algorithm/stream/validateOpenStream.h"

namespace tools {
namespace interface {
namespace import {

  columnData::columnData( const std::string& filePathIn )
  : my_ifstream( filePathIn, std::ifstream::in )
  {
    using algorithm::stream::validateOpenFile;
    
    validateOpenFile( my_ifstream );
    eliminateCommentLines();
  }

  auto columnData::saveDataLine( void ) noexcept -> void
  {
    using std::string;
    using algorithm::stream::getline;
    const string currentLine = getline( my_ifstream ) ;
    
    using algorithm::string::starts_with_not;
    const bool NotcommentLine = starts_with_not( currentLine, defaultIgnoreCharacter ) ;
    
    if( NotcommentLine ) {
      cleanFileStream << currentLine;
    }
  }

  auto columnData::eliminateCommentLines( void ) noexcept -> void
  {
    using algorithm::stream::not_eof;
    while( not_eof( my_ifstream ) ) {
      saveDataLine();
    }
  }

  auto columnData::updateCommentSymbol( const std::string& Symbol ) noexcept -> void
  {
    defaultIgnoreCharacter = Symbol;
    eliminateCommentLines();
  }


  auto columnData::changeIgnoreLines( const std::string& myChar ) noexcept -> void
  {
    defaultIgnoreCharacter = myChar ;
    
    using algorithm::stream::resetToBeginnging;
    using std::ifstream;
    
    resetToBeginnging( my_ifstream ) ;
    
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