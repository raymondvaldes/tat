#include "phase_analysis.h"

#include <cassert>

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_a_b1_b2_RC/fit_all/fit.hpp"
#include "thermal/analysis/oneLayer2D/finite_disk/centered_point/fit_a_s_RC/fit_all/fit.hpp"
#include "thermal/experimental/observations/slab/slab.hpp"
#include "thermal/model/optics/optics.h"
#include "optional/optional.h"

#include "thermal/analysis/oneLayer2D/finite_disk/fit_a_s_re_RC/fit_all/fit.hpp"
#include "thermal/analysis/oneLayer2D/finite_disk/fit_a_s_RC/fit_all/fit.hpp"
#include "thermal/analysis/oneLayer2D/finite_disk/fit_a_RC/fit_all/fit.hpp"
#include "thermal/analysis/oneLayer2D/finite_disk/fit_s_re_RC/fit_all/fit.hpp"
#include "thermal/analysis/oneLayer2D/finite_disk/fit_s_RC/fit_all/fit.hpp"
#include "thermal/analysis/oneLayer2D/finite_disk/fit_re_RC/fit_all/fit.hpp"

namespace gui_analysis{

using namespace units;
using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_a_b1_b2_RC::fit_all::fit;
using thermal::analysis::oneLayer2D::finite_disk::fit_a_s_re_RC::fit_all::fit;
using thermal::model::Optics;

auto phase_anaysis
(
  thermal::model::slab::Slab const & disk,
    thermal::model::Optics const & optics,

  thermal::equipment::laser::Modulation_frequencies const & frequencies,
  thermal::equipment::detector::Phases const & phases
)
noexcept ->
thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::Best_fit
{
  using thermal::experimental::observations::Slab;
  auto const view_radius = optics.view_radius;
  auto const beam_radius = optics.laser_radius;

  auto const specimen = Slab( disk, frequencies, phases, beam_radius );
  auto const best_fit =
      thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_a_b1_b2_RC::fit_all::fit( specimen, view_radius);
  return best_fit;
}

auto phase_anaysis_finite_disk
(
    thermal::model::slab::Slab const & disk,
    thermal::model::Optics const & optics,
    thermal::equipment::laser::Modulation_frequencies const & frequencies,
    thermal::equipment::detector::Phases const & phases,
    thermal::model::oneLayer2D::Parameter_selection const & parameter_selection
)
noexcept ->
thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::Best_fit
{
  using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::Best_fit;
  auto best_fit = optional< Best_fit >();
  using namespace thermal::analysis::oneLayer2D::finite_disk;

  if(
     parameter_selection.thermal_diffusivity == true  &&
     parameter_selection.specimen_radius == true &&
     parameter_selection.detector_view_radius == true &&
     parameter_selection.beam_radius == false
  ) {
      best_fit =
      fit_a_s_re_RC::fit_all::fit( frequencies, phases, disk, optics );
  }
  else if(
     parameter_selection.thermal_diffusivity == true  &&
     parameter_selection.specimen_radius == true &&
     parameter_selection.detector_view_radius == false &&
     parameter_selection.beam_radius == false

  ) {
      best_fit =
      fit_a_s_RC::fit_all::fit( frequencies, phases, disk, optics );
  }
  else if(
     parameter_selection.thermal_diffusivity == true  &&
     parameter_selection.specimen_radius == false &&
     parameter_selection.detector_view_radius == false &&
     parameter_selection.beam_radius == false     )
  {
      best_fit =
      fit_a_RC::fit_all::fit( frequencies, phases, disk, optics );
  }
  else if(
     parameter_selection.thermal_diffusivity == false  &&
     parameter_selection.specimen_radius == true &&
     parameter_selection.detector_view_radius == true &&
     parameter_selection.beam_radius == false     )
  {
      best_fit =
      fit_s_re_RC::fit_all::fit( frequencies, phases, disk, optics );
  }
  else if(
     parameter_selection.thermal_diffusivity == false  &&
     parameter_selection.specimen_radius == true &&
     parameter_selection.detector_view_radius == false  &&
      parameter_selection.beam_radius == false )
  {
      best_fit =
      fit_s_RC::fit_all::fit( frequencies, phases, disk, optics );
  }
  else if(
     parameter_selection.thermal_diffusivity == false  &&
     parameter_selection.specimen_radius == false &&
     parameter_selection.detector_view_radius == true  &&
     parameter_selection.beam_radius == false
   )
  {
      best_fit =
      fit_re_RC::fit_all::fit( frequencies, phases, disk, optics );
  }
  else {
 //  getchar();
  }

  return *best_fit;
}

auto phase_anaysis_finite_disk_centered_point
(
    thermal::model::slab::Slab const & disk,
    thermal::model::Optics const & optics,
    thermal::equipment::laser::Modulation_frequencies const & frequencies,
    thermal::equipment::detector::Phases const & phases
)
noexcept ->
thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::Best_fit
{  

  auto const best_fit =
      thermal::analysis::oneLayer2D::finite_disk::centered_point::fit_a_s_RC::fit_all::fit(
          frequencies, phases, disk, optics );
  return best_fit;
}

} // namespae gui_analysis

