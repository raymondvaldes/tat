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
#include <algorithm>

namespace algorithm {
namespace vector{
  
  template <typename Quantity >
  auto string2typename( const std::vector<std::string> & inputVector,
                        const Quantity unit_type  )
    -> std::vector< Quantity >
  {
    using std::vector;
    auto outputVector = vector< Quantity >( inputVector.size() );
    
    
    using std::string;
    const auto stringToDoubleInitilizer = [=]( const string& strng )
    {
      using std::stod;
      const auto myElectricity = Quantity( stod(strng) * unit_type );
      return myElectricity ;
    };
    
    using std::transform;
    transform (
      inputVector.begin(), inputVector.end(),
      outputVector.begin(), stringToDoubleInitilizer
      );
    
    return outputVector;
  };
  
}}

#endif
