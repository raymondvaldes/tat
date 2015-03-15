//
//  import_slab.h
//  tat
//
//  Created by Raymond Valdes_New on 3/14/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__import_slab__
#define __tat__import_slab__

#include <string>

#include "thermal/model/slab/slab.h"
#include "tools/interface/filesystem.hpp"

namespace thermal {

namespace model {

namespace slab {

auto
import
(
  filesystem::directory const & dir ,
  std::string const & filename
) -> Slab ;
  
} // namespace slab
  
} // namespace model
  
} // namespace thermal

#endif /* defined(__tat__import_slab__) */
