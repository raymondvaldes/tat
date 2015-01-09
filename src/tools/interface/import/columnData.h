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


namespace tools {
namespace interface {
namespace import {

class columnData{

private:
  
  mutable std::ifstream my_ifstream ;
  mutable std::stringstream cleanFileStream ;
  const std::string IgnoreCharacter ;
  
  mutable std::vector < std::vector<std::string> > rows;
  mutable std::vector < std::vector<std::string> > columns;
  
  auto saveDataLine( void ) noexcept
    -> void ;
  auto extractDataLines( void )  noexcept
    -> void ;

  auto verifyDataIntegrity(void) noexcept
    -> bool;
  auto resetDataVectors(void) noexcept
    -> void;
  auto processData( void )
    -> void;
  auto validateAndProcess(void) -> void;

public:

// Constructors and Destructors
  explicit columnData( const std::string& filePathIn );
  explicit columnData( const std::string& filePathIn,
                       const std::string& ignoreCharacterIn );

  auto getColumn( const size_t columnNumber ) noexcept
    -> std::vector<std::string>;
  
  auto getRow( const size_t rowNumber ) noexcept
    -> std::vector<std::string>;
  
  auto getElement( const size_t rowNumber, const size_t columnNumber ) noexcept
    -> std::string;
};



}}}



#endif /* defined(__tat__fileOpen__) */
