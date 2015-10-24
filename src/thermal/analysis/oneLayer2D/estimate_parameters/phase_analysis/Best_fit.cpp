//
//  Best_fit.cpp
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <cassert>
#include <iostream>

#include "plot/gnuplot.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/Best_fit.h"
#include "statistics/uncertainty_analysis/goodness_of_fit/goodness_of_fit.h"
#include "thermal/define/lthermal.h"
#include "units.h"


using thermal::define::thermalPenetrations_from_frequencies;

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace phase_analysis{


Best_fit::Best_fit
(
  thermal::model::slab::Slab const slab,
  thermal::model::Optics const optics,
  double const phase_goodness_of_fit
) noexcept :
  bulk_slab(slab),
  optics( optics ),
  phase_goodness_of_fit( phase_goodness_of_fit)
{}


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
  view_radius( view_radius_nd * slab_.thickness()  ),
  beam_radius( b * slab_.thickness() ),

  frequencies( frequencies_ ),
  ls( thermalPenetrations_from_frequencies(
        frequencies_,
        slab_.thermal_diffusivity() ,
        slab_.thickness()  ) ),
  model_phases( model_phases_ ),
  phase_goodness_of_fit( phase_goodness_of_fit_ ),
  optics(
    beam_radius,
    units::quantity< units::si::heat_flux>(100000. * units::si::watt/ units::si::square_meter),
    view_radius, 1
  )
{
  assert( phase_goodness_of_fit > 0 );
  assert( !frequencies.empty() );
  

}

Best_fit::Best_fit
(
  thermal::model::slab::Slab const slab_,
  units::quantity< units::si::dimensionless > const view_radius_nd,
  units::quantity< units::si::dimensionless> const b,
  std::vector< units::quantity<units::si::frequency> > const frequencies_,
  std::vector< units::quantity<units::si::plane_angle > > const model_phases_,
  double const phase_goodness_of_fit_,
  units::quantity< units::si::dimensionless > const view_radius_offset_input
) noexcept :
  Best_fit( slab_, view_radius_nd, b, frequencies_, model_phases_, phase_goodness_of_fit_ )
{
  view_radius_offset = view_radius_offset_input * slab_.thickness()  ;
}

void Best_fit::plot_model_phases_against(
  std::vector< units::quantity< units::si::plane_angle > > const & exp_phases
) const
{
  plot::simple_x_y1_y2( frequencies, model_phases, exp_phases );
}

void Best_fit::plot_model_phases_against_observations( void ) const
{
  assert( !frequencies.empty() );
  assert( !model_phases.empty() );
  assert( !observations.empty() );

  assert( frequencies.size() == observations.size() ) ;
  assert( frequencies.size() == model_phases.size() ) ;

  plot::simple_x_y1_y2( frequencies, model_phases, observations );
}

auto Best_fit::phase_goodness_of_fit_function() const -> double
{
//  auto const predictions = model_predictions.phases();
//  auto const gf = goodness_of_fit( calibrated_observations , predictions );

  auto const gf = 42;
  return gf;
}





} // namespace phase_analysis
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
