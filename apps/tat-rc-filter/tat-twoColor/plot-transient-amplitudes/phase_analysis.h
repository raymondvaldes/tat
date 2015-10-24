#ifndef PHASE_ANALYSIS_H
#define PHASE_ANALYSIS_H

#include "thermal/experimental/observations/slab/slab.hpp"
#include "thermal/equipment/detector/view_radius.h"
#include "thermal/equipment/laser/Beam_radius.h"
#include "thermal/equipment/laser/modulation_frequencies.h"

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/Best_fit.h"
#include "thermal/equipment/detector/phases.h"
#include "thermal/model/oneLayer2D/model_selection.h"

namespace gui_analysis{

  auto phase_anaysis
  (
      thermal::model::slab::Slab const & disk, const thermal::model::Optics &optics,
      thermal::equipment::laser::Modulation_frequencies const & frequencies,
      thermal::equipment::detector::Phases const & phases
  )
  noexcept ->
  thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::Best_fit;


  auto phase_anaysis_finite_disk
  (
      thermal::model::slab::Slab const & disk, const thermal::model::Optics &optics,
      thermal::equipment::laser::Modulation_frequencies const & frequencies,
      thermal::equipment::detector::Phases const & phases,
      thermal::model::oneLayer2D::Parameter_selection const & parameter_selection
  )
  noexcept ->
  thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::Best_fit;


  auto phase_anaysis_finite_disk_centered_point
  (
      thermal::model::slab::Slab const & disk, const thermal::model::Optics &optics,
      thermal::equipment::laser::Modulation_frequencies const & frequencies,
      thermal::equipment::detector::Phases const & phases)
  noexcept ->
  thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::Best_fit;





}

#endif // PHASE_ANALYSIS_H
