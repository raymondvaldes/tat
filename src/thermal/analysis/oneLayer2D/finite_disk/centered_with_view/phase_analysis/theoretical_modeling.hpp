//
//  theoretical_modeling.hpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef theoretical_modeling_hpp_102315
#define theoretical_modeling_hpp_102315

#include "thermal/emission/phases.h"
#include "thermal/model/complex/temperatures.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"

#include "thermal/equipment/laser/modulation_frequencies.h"
#include "electronics/filter/low-pass/RC-first-order/time_constant.h"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

struct Theoretical_modeling {
  emission::Phases observations;
  model::complex::Temperatures model_predictions;
  emission::Phases experimental_bias;
  emission::Phases calibrated_observations;
  
  Theoretical_modeling(
    emission::Phases const & observations_,
    model::complex::Temperatures const & model_predictions_,
    emission::Phases const & experimental_bias_
  );
  
  auto phase_goodness_of_fit() const noexcept -> double;
  
};

auto theoretical_modeling(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & experimental_phases,
  
  std::function< std::tuple<
    model::slab::Slab,
    model::Optics>
    ( const double * x ) > const & model_updater
  
) noexcept -> std::function< Theoretical_modeling( const double *x  ) >;
  

} } } } } }

#endif /* theoretical_modeling_hpp */
