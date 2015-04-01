//
//  import_heating_properties.h
//  tat
//
//  Created by Raymond Valdes on 4/1/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_import_heating_properties_h
#define tat_import_heating_properties_h

#include <string>

#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "tools/interface/xml.h"
#include "tools/interface/filesystem.hpp"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless {

auto import_heating_properties
(
  filesystem::directory const & dir ,
  std::string const & filename
) -> HeatingProperties;

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal


#endif
