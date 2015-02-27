//
//  VectorString2Typename.h
//  tat
//
//  Created by Raymond Valdes on 1/14/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_VectorString2Typename_h
#define tat_VectorString2Typename_h

#include <vector>
#include <string>
#include "algorithm/algorithm.h"

namespace algorithm {
namespace vector{
  
template <typename Quantity >
auto string_to_quantity( const std::vector<std::string> & inputVector,
                         const Quantity units  ) noexcept
-> std::vector< Quantity >
{
  using std::vector;
  using std::string;
  using algorithm::transform;
  
  const auto stringToDoubleInitilizer = [=]( const string & strng )
  {
    using std::stod;
    return Quantity( stod(strng) * units ) ;
  };


  auto outputVector = vector< Quantity >( inputVector.size() );
  
  transform( inputVector, outputVector.begin(), stringToDoubleInitilizer );
  
  return outputVector;
};
  

//template <typename Quantity >
//auto string_to_quantity( const std::vector<std::string> & inputVector,
//                         const Quantity units  ) noexcept
//-> std::vector< Quantity >
//{
//  using std::vector;
//  using std::string;
//  using algorithm::transform;
//  
//  const auto stringToDoubleInitilizer = [=]( const string & strng )
//  {
//    using std::stod;
//    return Quantity( stod(strng) * units ) ;
//  };
//
//
//  auto outputVector = vector< Quantity >( inputVector.size() );
//  
//  transform( inputVector, outputVector.begin(), stringToDoubleInitilizer );
//  
//  return outputVector;
//};
  
  
}}

#endif
