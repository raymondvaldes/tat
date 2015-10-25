//
//  theoretical_modeling.hpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef theoretical_modeling_hpp34uyhuh34uh
#define theoretical_modeling_hpp34uyhuh34uh

#include "thermal/emission/phases.h"
#include "thermal/model/complex/temperatures.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"

#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/analysis/oneLayer2D/theoretical_results.hpp"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D {

auto theoretical_modeling(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,

  std::function< std::tuple<
    model::slab::Slab,
    model::Optics>
    ( const double * x ) > const & model_updater,
    
  std::function<
    thermal::model::complex::Temperatures(
      model::slab::Slab const &,
      model::Optics const &,
      equipment::laser::Modulation_frequencies const &
      )  > const & frequency_sweep
  
) noexcept -> std::function< Theoretical_results( const double *x  ) >;
  

} } }
#endif /* theoretical_modeling_hpp */
