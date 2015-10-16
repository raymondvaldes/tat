#ifndef AMPLITUDE_ANALYSIS_H
#define AMPLITUDE_ANALYSIS_H


#include "gTBC/gMeasure/gTBD/meta_measurement_descriptions.hpp"
#include "thermal/equipment/detector/signal.h"
#include "thermal/pyrometry/twoColor/calibration/Coefficient.h"
#include "thermal/pyrometry/twoColor/set_phase.h"
#include "thermal/pyrometry/twoColor/periodic/transient_analysis_sweep_results.h"

namespace gui_analysis{

auto amplitude_analysis(
  gTBC::gMeasure::meta_measurement_descriptions const & file_lambda_1,
  gTBC::gMeasure::meta_measurement_descriptions const & file_lambda_2,
  const thermal::equipment::detector::Signal DC_1,
  const thermal::equipment::detector::Signal DC_2,
  thermal::pyrometry::twoColor::calibration::Coefficient const gCoefficient,
  thermal::pyrometry::twoColor::Set_phase const set_phase
) noexcept -> thermal::pyrometry::twoColor::periodic::transient_analysis_sweep_results;

}


#endif // AMPLITUDE_ANALYSIS_H
