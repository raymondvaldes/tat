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
#include <tuple>


namespace tools {

namespace interface {

namespace import {

struct dimensions{

  size_t rows;
  size_t columns;
  size_t elements;
  
  dimensions(
    size_t const rows_,
    size_t const columns_,
    size_t const elements_
  );
};

class columnData{

private:
  
  mutable std::ifstream my_ifstream ;
  mutable std::stringstream cleanFileStream ;
//  std::string IgnoreCharacter ;
  std::vector< std::string > IngoreCharacters;
  
  mutable std::vector < std::vector<std::string> > rows;
  mutable std::vector < std::vector<std::string> > columns;
  
  auto saveDataLine( void ) noexcept
    -> void ;
  
  auto extract_file_to_stream( void )  noexcept
    -> void ;

  auto verifyDataIntegrity(void) noexcept
    -> bool;
  
  auto clearDataVectors(void) 
    -> void;
  
  auto processData( void ) 
    -> void;
  
  auto validateAndProcess(void)
    -> void;

public:

// Constructors and Destructors
  explicit columnData( std::string const & filePathIn );
  
  explicit columnData( std::string const & filePathIn,
                       std::vector<std::string> const & ignoreCharactersIn );

  auto getColumn( size_t const columnNumber ) const noexcept
    -> std::vector<std::string>;
  
  auto getRow( size_t const rowNumber ) const noexcept
    -> std::vector<std::string>;
  
  auto getElement( size_t const rowNumber, size_t const columnNumber ) const noexcept
    -> std::string;
  
  auto size(void) const noexcept -> dimensions;
  };

} // namespace tools

} // namespace interface

} // namespace import



#endif /* defined(__tat__fileOpen__) */
