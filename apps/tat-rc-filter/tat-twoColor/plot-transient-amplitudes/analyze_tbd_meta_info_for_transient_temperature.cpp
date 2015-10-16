//#include "analyze_tbd_meta_info_for_transient_temperature.h"

//#include <cassert>

//#include "thermal/pyrometry/twoColor/periodic/analysis_from_properties_sweep.h"
//#include "gTBC/gMeasure/gTBD/process_twoColor_TBD_meta_data.hpp"

//namespace gui_analysis{

//using thermal::pyrometry::twoColor::calibration::Coefficient;
//using thermal::pyrometry::twoColor::periodic::analysis_from_properties_sweep;
//using thermal::equipment::detector::Signal;
//using thermal::pyrometry::twoColor::Set_phase;
//using gTBC::gMeasure::process_twoColor_TBD_meta_data;

//auto analyze_tbd_meta_info_for_transient_temperature
//(
//  gTBC::gMeasure::meta_measurement_descriptions const & file_lambda_1,
//  gTBC::gMeasure::meta_measurement_descriptions const & file_lambda_2,
//  Signal const DC_1,
//  Signal const DC_2,
//  Coefficient const gCoefficient,
//  Set_phase const set_phase
//) noexcept ->
//thermal::pyrometry::twoColor::periodic::transient_analysis_sweep_results
//{
//  assert( DC_1.value() > 0 );
//  assert( DC_2.value() > 0 );

//  auto const processed_files = process_twoColor_TBD_meta_data(
//    file_lambda_1,
//    file_lambda_2,
//    gCoefficient,
//    DC_1,
//    DC_2,
//    set_phase
//  );

//  auto const temperature_analysis =
//      analysis_from_properties_sweep( processed_files, gCoefficient );

//  return temperature_analysis;
//}

//}
