#include "phase_analysis.h"

#include <cassert>

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_a_b1_b2_RC/fit_all/fit.hpp"
#include "thermal/experimental/observations/slab/slab.hpp"

namespace gui_analysis{

using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_a_b1_b2_RC::fit_all::fit;

auto phase_anaysis
(
  thermal::model::slab::Slab const & disk,
  thermal::equipment::laser::Modulation_frequencies const & frequencies,
  thermal::equipment::detector::Phases const & phases,
  thermal::equipment::laser::Beam_radius const & beam_radius,
  thermal::equipment::detector::View_radius const & view_radius
)
noexcept ->
thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::Best_fit
{
  using thermal::experimental::observations::Slab;

  auto const specimen = Slab( disk, frequencies, phases, beam_radius );
  auto const best_fit = fit( specimen, view_radius);
  return best_fit;
}


} // namespae gui_analysis

