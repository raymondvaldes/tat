//
//  fit.hpp
//  tat
//
//  Created by Raymond Valdes on 10/19/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_hpp_19uj3e9uj319ec3
#define fit_hpp_19uj3e9uj319ec3

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/Best_fit.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/emission/phases.h"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

auto fit_b_re_RC
(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & phases,
  model::slab::Slab const & slab_initial,
  model::Optics const & optics
)
noexcept -> estimate_parameters::phase_analysis::Best_fit;

} } } } } }

#endif /* fit_hpp */
