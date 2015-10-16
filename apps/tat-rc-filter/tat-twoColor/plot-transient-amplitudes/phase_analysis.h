#ifndef PHASE_ANALYSIS_H
#define PHASE_ANALYSIS_H

#include "thermal/experimental/observations/slab/slab.hpp"
#include "thermal/equipment/detector/view_radius.h"
#include "thermal/equipment/laser/Beam_radius.h"
#include "thermal/equipment/laser/modulation_frequencies.h"

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/Best_fit.h"
#include "thermal/equipment/detector/phases.h"

namespace gui_analysis{

  auto phase_anaysis
  (
      thermal::model::slab::Slab const & disk,
      thermal::equipment::laser::Modulation_frequencies const & frequencies,
      thermal::equipment::detector::Phases const & phases,
      thermal::equipment::laser::Beam_radius const & beam_radius,
      thermal::equipment::detector::View_radius const & view_radius
  )
  noexcept ->
  thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::Best_fit;
}

#endif // PHASE_ANALYSIS_H
