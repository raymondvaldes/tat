//
//  phase_fitting.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>

#include "investigations/twoColorPyrometery/phase_fitting.h"
#include "thermal/model/slab/slab.h"


namespace investigations {

namespace twoColorPyrometery {

auto phase_fitting( filesystem::directory const & dir ) -> void
{
  
  using thermal::model::slab::neumann_and_direchlet_BC;

  std::cout << "hello, world!\n";



}
  
} // namespace twoColorPyrometery
  
} // namespace investigations
