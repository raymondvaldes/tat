//
//  Best_fit.cpp
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <cassert>

#include "thermal/analysis/oneLayer2D/estimate_parameters/weighted_average/Best_fit.h"
#include "thermal/define/lthermal.h"

using thermal::define::thermalPenetrations_from_frequencies;

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace weighted_average{

Best_fit::Best_fit
(
  thermal::model::slab::Slab const slab_,

  units::quantity< units::si::dimensionless > const view_radius_nd,
  units::quantity< units::si::dimensionless> const b,
 
  std::vector< units::quantity<units::si::frequency> > const frequencies_,
  std::vector< units::quantity< units::si::plane_angle > > const model_phases_,
  double phase_goodness_of_fit_
) noexcept :
  bulk_slab( slab_ ),
  view_radius( view_radius_nd * bulk_slab.characteristic_length ),
  beam_radius( b * bulk_slab.characteristic_length ),

  frequencies( frequencies_ ),
  ls( thermalPenetrations_from_frequencies(
        frequencies_,
        slab_.get_diffusivity() ,
        slab_.characteristic_length ) ),
  model_phases( model_phases_ ),
  phase_goodness_of_fit( phase_goodness_of_fit_ )
{
  assert( phase_goodness_of_fit > 0 );
  assert( !frequencies.empty() );
}

} // namespace weighted_average
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
