//
//  theoretical_modeling.hpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef theoretical_modeling_hpp_102415
#define theoretical_modeling_hpp_102415

#include "thermal/emission/phases.h"
#include "thermal/model/complex/temperatures.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"

#include "thermal/equipment/laser/modulation_frequencies.h"
#include "electronics/filter/low-pass/RC-first-order/time_constant.h"

namespace thermal{
namespace analysis{
namespace oneLayer2D {

struct Theoretical_results {
  model::complex::Temperatures observations;
  model::complex::Temperatures model_predictions;
  emission::Phases experimental_bias;
  emission::Phases calibrated_observations;
  
  Theoretical_results(
    model::complex::Temperatures const & observations_,
    model::complex::Temperatures const & model_predictions_,
    emission::Phases const & experimental_bias_
  );
  
  auto phase_goodness_of_fit() const noexcept -> double;
  
};

} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal

#endif /* theoretical_modeling_hpp */
