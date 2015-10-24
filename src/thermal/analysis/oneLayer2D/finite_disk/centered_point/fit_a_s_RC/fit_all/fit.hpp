//
//  fit.hpp
//  tat
//
//  Created by Raymond Valdes on 10/21/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fit_hpp
#define fit_hpp

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/Best_fit.h"
#include "thermal/experimental/observations/slab/slab.hpp"

#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/emission/phases.h"

namespace thermal {
namespace analysis {
namespace oneLayer2D{
namespace finite_disk {
namespace centered_point {
namespace fit_a_s_RC {
namespace fit_all{

auto fit
(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & phases,
  model::slab::Slab const & slab_initial,
  model::Optics const & optics
)
noexcept -> estimate_parameters::phase_analysis::Best_fit;

} } } } } } }

#endif /* fit_hpp */
