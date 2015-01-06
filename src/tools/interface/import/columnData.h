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

//#include "algorithm/stream/getline.h"

namespace tools {
namespace interface {
namespace import {

class columnData{

private:
  
  std::ifstream my_ifstream ;
  std::stringstream cleanFileStream ;
  mutable std::string defaultIgnoreCharacter = "#" ;
  
  auto NumberOfColumns(void)          noexcept -> size_t;
  auto NumberofRows(void)             noexcept -> size_t;
  auto completeMatrix(void)           noexcept -> bool;

  auto saveDataLine( void )           noexcept -> void ;
  auto eliminateCommentLines( void )  noexcept -> void ;
  auto changeIgnoreLines( const std::string& myChar )   noexcept -> void ;
  auto updateCommentSymbol( const std::string& Symbol ) noexcept -> void ;

public:

// Constructors and Destructors
  explicit columnData( const std::string& filePathIn );
  ~columnData( void ) noexcept {} ;
  
  
// Template functions
  template< class T>
  auto getColumn( const size_t columnNumber ) noexcept -> std::vector<T>
  {
    using std::vector;
    vector< T > myColumn(0) ;
    
//    myColumn.push_back( algorithm::stream::getline( cleanFileStream ) );
    
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