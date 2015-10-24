//
//  fit.hpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_hpp_102415
#define fit_hpp_102415

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/Best_fit.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/emission/phases.h"
#include "thermal/model/oneLayer2D/finite_disk/parameter_list.hpp"
#include "thermal/model/complex/temperatures.h"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

auto fit
(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,
  model::slab::Slab const & slab_initial,
  model::Optics const & optics_initial,
  model::oneLayer2D::finite_disk::Parameters const & parameters
)
noexcept -> estimate_parameters::phase_analysis::Best_fit;

} } } } } }

#endif /* fit_hpp */
