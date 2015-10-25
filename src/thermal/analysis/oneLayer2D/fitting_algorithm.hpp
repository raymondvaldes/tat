//
//  fitting_algorithm.hpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef fitting_algorithm_hpp_102515f43f34f
#define fitting_algorithm_hpp_102515f43f34f

#include <functional>
#include <tuple>
#include <vector>

#include "thermal/emission/phases.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/model/complex/temperatures.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "best_fit.hpp"
#include "theoretical_results.hpp"

namespace thermal{
namespace analysis{
namespace oneLayer2D{

auto fitting_algorithm
(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,

  std::pair< std::vector<double> ,
    std::function<
    std::tuple<
      model::slab::Slab,
      model::Optics  >( const double * x )  >
      > const & system,

  std::function<
    model::complex::Temperatures(
        model::slab::Slab const &,
        model::Optics const &,
        equipment::laser::Modulation_frequencies const & )
  > const & frequency_sweep,

   std::function<  std::function< void( const double *, double * ) >(std::function< Theoretical_results( const double *  ) > const &)   >
  const &  minimization_equation
)
noexcept -> Best_fit;


} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal

#endif /* fitting_algorithm_hpp */
