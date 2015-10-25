//
//  theoretical_modeling.cpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "theoretical_modeling.hpp"

#include "electronics/filter/low-pass/RC-first-order/phase_shifts_from_input.hpp"


namespace thermal {
namespace analysis { 
namespace oneLayer2D {

using std::get;
using electronics::filter::low_pass::RC_first_order::phase_shifts_from_input;


auto theoretical_modeling(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,
  std::function< std::tuple<
    model::slab::Slab,
    model::Optics >
    ( const double * x ) > const & model_updater,

  std::function<
    thermal::model::complex::Temperatures(
      model::slab::Slab const &,
      model::Optics const &,
      equipment::laser::Modulation_frequencies const &
      )  > const & frequency_sweep

) noexcept -> std::function< Theoretical_results( const double *x  ) >
{

  auto const func =
  [frequencies, &model_updater, temperatures, frequency_sweep]
  ( const double *x ) noexcept
  {
    auto const t = model_updater( x );
  
    auto const slab = get< 0 >(t);
    auto const optics = get< 1 >(t);

    auto const modeling = frequency_sweep( slab, optics, frequencies );
    auto const phase_bias =
    phase_shifts_from_input( frequencies, optics.filter_constant );
    
    auto const output =
    Theoretical_results( frequencies, temperatures, modeling, phase_bias );
  
    return output;
  };
  
  return func;
}

} } }
