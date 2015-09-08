//
//  use_engineering_prefix.cpp
//  tat
//
//  Created by Raymond Valdes on 9/1/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "use_engineering_prefix.hpp"

namespace units{

using std::cout;

auto use_engineering_prefix( void ) noexcept -> void
{
  cout << engineering_prefix;
}

} // using namespace units
