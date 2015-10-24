//
//  theoretical_modeling.cpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "theoretical_modeling.hpp"
#include "algorithm/vector/add.h"
#include "electronics/filter/low-pass/RC-first-order/phase_shifts_from_input.hpp"
#include "thermal/model/oneLayer2D/finite_disk/emission/centered_detector_with_view/frequency_sweep.hpp"
namespace thermal {
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

using std::get;
using algorithm::vector::add;
using electronics::filter::low_pass::RC_first_order::phase_shifts_from_input;
using model::oneLayer2D::finite_disk::disk::emission::centered_detector_with_view::frequency_sweep;

Theoretical_modeling::Theoretical_modeling(
  emission::Phases const & observations_,
  model::complex::Temperatures const & model_predictions_,
  emission::Phases const & experimental_bias_
)
: observations( observations_ ),
  model_predictions( model_predictions_ ),
  experimental_bias( experimental_bias_ ),
  calibrated_observations( add( observations, experimental_bias ) )
  //calibrated_observations(observations )  //enable this to ignore RC filter
{};


auto theoretical_modeling(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & experimental_phases,
  
  std::function< std::tuple<
    model::slab::Slab,
    model::Optics >
    ( const double * x ) > const & model_updater
  
) noexcept -> std::function< Theoretical_modeling( const double *x  ) >
{
  auto const func =
  [frequencies, model_updater, experimental_phases]
  ( const double *x ) noexcept
  {
    auto const t = model_updater( x );
  
    auto const slab = get< 0 >(t);
    auto const optics = get< 1 >(t);

    auto const modeling = frequency_sweep( slab, optics, frequencies );
    auto const phase_bias = phase_shifts_from_input( frequencies, optics.filter_constant );
    auto const output =
    Theoretical_modeling( experimental_phases, modeling, phase_bias );
  
    return output;
  };
  
  return func;
}

} } } } } }
