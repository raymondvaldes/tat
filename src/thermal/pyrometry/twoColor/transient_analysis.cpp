//
//  transient_analysis.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include <utility>

#include "thermal/pyrometry/twoColor/transient_analysis.h"
#include "thermal/pyrometry/twoColor/normalizedDetectorMeasurements.h"
#include "math/functions/periodicData.h"
#include "math/functions/PeriodicProperties.h"
#include "math/curveFit/cosine.h"
#include "physics/classical_mechanics/kinematics.h"

#include "tools/interface/filesystem.hpp"
#include "gnuplot-iostream.h"
#include "algorithm/vector/quantityTodouble.h"
namespace thermal {

namespace pyrometry {

namespace twoColor {

using units::quantity;
using units::si::radians;
using units::si::one_over_temperature;
using units::si::temperature;
using units::si::plane_angle;
using units::si::time;
using units::si::dimensionless;
using units::pow;

using math::functions::PeriodicData;
using math::functions::PeriodicProperties;
using math::curveFit::cosine;
using math::functions::Cosine;
using physics::classical_mechanics::frequency_to_angularFrequency;

using std::pair;
using std::vector;
using std::make_pair;
using algorithm::vector::quantityTodouble;

auto transient_analysis_results::plot_normalized_SR_exp_model( void )
const noexcept -> void
{
  
	Gnuplot gp("/usr/local/bin/gnuplot --persist");
  
  gp << "set xlabel 'time (s)'" << "\n";
  gp << "set ylabel 'normalized signal ratio (1/K)'" << "\n";
  
  auto const x_pts = quantityTodouble( normalized_SRs.first );
  
  auto const y1_pts = quantityTodouble( normalized_SRs.second );
  auto const xy1_pts = make_pair( x_pts, y1_pts );
  
  auto shifted_cosine = fitted_cosine_function;
  shifted_cosine.shift_phase( laser_modulation_phase );
  auto const y2 = shifted_cosine.evaluate( normalized_SRs.first );
  auto const y2_pts = quantityTodouble( y2 );
  auto const xy2_pts = make_pair( x_pts, y2_pts );
  
  
  using units::quantity_to_string;
  gp  << "set label \"T_{steady} ="    << steady_temperature.value()
      << "[K] \" at 2,0.001739" << "\n";
  
  gp  << "set label \"T_{phase} ="     << transient_temperature_phase.value()
      << "[K] \" at 2,0.001738" << "\n";
  
  gp  << "set label \"T_{transient} =" << transient_temperature_amplitude.value()
      << "[K] \" at 2,0.001737" << "\n";
  
  gp  << "set label \"frequency =" << laser_modulation_w.value() / (2*M_PI)
      << "[hz]\" at 2,0.001736" << "\n";

  
  gp << "plot"
  << gp.file1d( xy1_pts ) << "with points title 'experimental SR_{norm}',"
  << gp.file1d( xy2_pts ) << "with lines title 'best-fit SR_{norm}'" << std::endl;
  
  // add labels
}


auto transient_analysis
(
  thermal::equipment::detector::Measurements const & measurements_1,
  thermal::equipment::detector::Measurements const & measurements_2,
  units::quantity< units::si::dimensionless > const & gCoeff,
  units::quantity< units::si::frequency > const & laser_frequency,
  units::quantity< units::si::plane_angle > const & laser_phase )
noexcept -> transient_analysis_results
{
  auto const omega = frequency_to_angularFrequency( laser_frequency );
  
  auto const normalized_SRs =
  normalizedDetectorMeasurements( measurements_1, measurements_2, gCoeff );

  auto const myPeriodicData =
  PeriodicData< one_over_temperature >( normalized_SRs ) ;
  
  auto const initialConditions =
  PeriodicProperties<one_over_temperature>{
    myPeriodicData.initialEstimateOffset(),
    myPeriodicData.initialEstimateAmplitude(),
    omega,
    quantity<plane_angle>{ -M_PI/2* radians }
  } ;

  auto const fitted_cosine_function =
  cosine( normalized_SRs, initialConditions, laser_phase );

  auto const myFittedAmplitude = abs(fitted_cosine_function.get_amplitude()) ;
  auto const myFittedOffset = fitted_cosine_function.get_offset() ;
  
  auto  const transient_temperature_phase = fitted_cosine_function.get_phase() ;
    
  auto const steady_temperature =
  quantity<temperature>( quantity<dimensionless>{1} / myFittedOffset ) ;
  
  auto const transient_temperature_amplitude =
  myFittedAmplitude * pow<2>( steady_temperature );

  auto const output =
  transient_analysis_results
  (
    steady_temperature,
    transient_temperature_phase,
    transient_temperature_amplitude,
    normalized_SRs,
    fitted_cosine_function,
    omega,
    laser_phase
  );

  return output;
}

  
} // namespace twoColor
  
} // namespace napyrometryme
  
} // namespace thermal
