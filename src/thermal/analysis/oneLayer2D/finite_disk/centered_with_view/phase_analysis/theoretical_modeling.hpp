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
#include "thermal/analysis/oneLayer2D/theoretical_results.hpp"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

auto theoretical_modeling(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & experimental_phases,
//    model::complex::Temperatures const & experimental_phases,

  std::function< std::tuple<
    model::slab::Slab,
    model::Optics>
    ( const double * x ) > const & model_updater
  
) noexcept -> std::function< Theoretical_results( const double *x  ) >;
  

} } } } } }

#endif /* theoretical_modeling_hpp */
