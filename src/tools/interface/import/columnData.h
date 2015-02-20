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
  std::string IgnoreCharacter ;
  
  mutable std::vector < std::vector<std::string> > rows;
  mutable std::vector < std::vector<std::string> > columns;
  
  auto saveDataLine( void ) noexcept
    -> void ;
  
  auto extract_file_to_stream( void )  noexcept
    -> void ;

  auto verifyDataIntegrity(void) noexcept
    -> bool;
  
  auto clearDataVectors(void) noexcept
    -> void;
  
  auto processData( void )
    -> void;
  
  auto validateAndProcess(void)
    -> void;

public:

// Constructors and Destructors
  explicit columnData( std::string const & filePathIn );
  
  explicit columnData( std::string const & filePathIn,
                       std::string const & ignoreCharacterIn );

  auto getColumn( size_t const columnNumber ) const noexcept
    -> std::vector<std::string>;
  
  auto getRow( size_t const rowNumber ) const noexcept
    -> std::vector<std::string>;
  
  auto getElement( size_t const rowNumber, size_t const columnNumber ) const noexcept
    -> std::string;
  
  auto size(void) const noexcept -> size_t;
};



}}}



#endif /* defined(__tat__fileOpen__) */
