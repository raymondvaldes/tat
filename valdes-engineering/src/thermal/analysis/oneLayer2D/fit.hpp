//
//  fit.hpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_hpp_102415
#define fit_hpp_102415

#include "best_fit.hpp"
#include "fit_selection.h"

#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/model/complex/temperatures.h"
#include "thermal/model/oneLayer2D/parameter_list.hpp"
#include "thermal/model/oneLayer2D/generator/disk.hpp"

namespace thermal{
namespace analysis{
namespace oneLayer2D{

auto fit(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,
  Fit_selection const fit_selection,
  model::oneLayer2D::generator::Disk const & initial_disk,
  model::oneLayer2D::Parameters const & parameters  
)
-> Best_fit;

}}}

#endif /* fit_hpp */
