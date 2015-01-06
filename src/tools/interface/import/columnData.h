//
//  fileOpen.h
//  tat
//
//  Created by Raymond Valdes on 1/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__fileOpen__
#define __tat__fileOpen__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "algorithm/string/starts_with.h"
#include "algorithm/stream/resetInputBeginning.h"

namespace tools {
namespace interface {
namespace import {

class columnData{

private:
  
  std::ifstream inputFileStream ;
  std::ostringstream cleanFileStream;
  mutable std::string defaultIgnoreCharacter = "#" ;
  
  auto validateOpenFile( void ) -> void ;
  auto saveDataLine( void ) noexcept -> void ;

  auto NumberOfColumns(void) noexcept -> size_t;
  auto NumberofRows(void) noexcept -> size_t ;
  
public:

// Constructors and Destructors
  explicit columnData( const std::string& filePathIn );
  
  ~columnData( void ) noexcept {} ;
  
  
// Helper functions
  auto eliminateCommentLines( void ) noexcept -> void ;
  
  auto endOfFile( void ) noexcept -> bool ;
  
  auto NotEOF( void ) noexcept -> bool ;
  
  auto updateCommentSymbol( const std::string& Symbol ) noexcept -> void ;
  
  auto readLine( void ) noexcept -> std::string ;
  
  auto rejectLine( const std::string& line ) noexcept -> bool;
  
  auto changeIgnoreLines( const std::string& myChar ) noexcept -> void ;
  
  auto file_is_open( void ) const noexcept -> bool ;
  
  auto file_is_closed( void ) const noexcept -> bool ;
  
// Template functions
  template< class T>
  auto getColumn( const size_t columnNumber ) noexcept -> std::vector<T>
  {
    const std::vector< T > myColumn ;
    
    
    
    
    
    return myColumn;
  }
  
  template< class T>
  auto getRow( const size_t columnNumber ) noexcept -> std::vector<T>
  {
    const std::vector< T > myColumn( columnNumber ) ;
    
    return myColumn;
  }
  
};



}}}



#endif /* defined(__tat__fileOpen__) */