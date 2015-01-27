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
auto string2typename( const std::vector<std::string> & inputVector,
                      const Quantity unit_type  )
  -> std::vector< Quantity >
{
  using std::vector;
  using std::string;
  using std::transform;
  
  const auto stringToDoubleInitilizer = [=]( const string& strng )
  {
    using std::stod;
    return Quantity( stod(strng) * unit_type ) ;
  };


  auto outputVector = vector< Quantity >( inputVector.size() );
  
  algorithm::transform(
  inputVector, outputVector.begin(), stringToDoubleInitilizer );
  
  return outputVector;
};
  
}}

#endif
