//
//  import_sweep_meta_data.h
//  tat
//
//  Created by Raymond Valdes_New on 3/18/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__import_sweep_meta_data__
#define __tat__import_sweep_meta_data__

#include <vector>
#include "tools/interface/filesystem.hpp"
#include "units.h"

#include "gTBC/gMeasure/gTBD/meta_measurement_descriptions.hpp"

namespace gTBC {
namespace gMeasure {

auto
import_sweep_meta_data( filesystem::path const & path )
-> meta_measurement_descriptions;

} // namespace gMeasure
} // namespace gTBC

#endif /* defined(__tat__import_sweep_meta_data__) */
