//
//  fitting_algorithm.hpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fitting_algorithm_hpp_102315
#define fitting_algorithm_hpp_102315

#include <functional>
#include <tuple>
#include <vector>

#include "thermal/emission/phases.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/model/complex/temperatures.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/Best_fit.h"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

auto fitting_algorithm
(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & exp_phases,
  std::vector<double> & model_parameters,
  std::function<
  std::tuple<
    model::slab::Slab,
    model::Optics  >
  ( const double * x)> const & model_evaluate
)
noexcept -> estimate_parameters::phase_analysis::Best_fit;

} } } } } }

#endif /* fitting_algorithm_hpp */
