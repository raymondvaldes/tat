//
//  readLine.h
//  tat
//
//  Created by Raymond Valdes on 1/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__readLine__
#define __tat__readLine__

#include <string>
#include <iostream>
#include <sstream>

namespace algorithm {
namespace stream {

  inline auto getline( std::istream& inputStream ) noexcept -> std::string
  {
    using std::string;
    using std::getline;

    string getsThisLine ;
    getline( inputStream , getsThisLine, '\n' ) ;
    
    return getsThisLine ;
  }

}}

#endif /* defined(__tat__readLine__) */
