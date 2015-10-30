//
//  meta_measurement_description.cpp
//  tat
//
//  Created by Raymond Valdes on 10/13/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "meta_measurement_description.hpp"

namespace gTBC {
namespace gMeasure {

meta_measurement_description::meta_measurement_description
(
  units::quantity< units::si::frequency> const laser_modulation_frequency_,
  units::quantity< units::si::wavelength> const monochrometer_wavelength_,
  
  units::quantity< units::si::plane_angle> const signal_phase_,
  units::quantity< units::si::electric_potential> const signal_amplitude_,
  units::quantity< units::si::dimensionless > const reference_amplitude_,
  
  units::quantity< units::si::dimensionless, size_t> const signals_averaged_,
  units::quantity< units::si::dimensionless> const signal_to_noise_,
  units::quantity< units::si::dimensionless> const running_signal_to_noise_,
  
  units::quantity< units::si::dimensionless> const laser_modulation_amplitude_,
  units::quantity< units::si::dimensionless> const laser_modulation_offset_,
  units::quantity< units::si::dimensionless> const laser_pulse_width_,
  
  units::quantity< units::si::plane_angle> const reference_argument_,
  units::quantity< units::si::plane_angle> const reference_argument_um_,

  units::quantity< units::si::dimensionless, size_t> const samples_,
  units::quantity< units::si::time> const measurement_time_,
  
  units::quantity< units::si::electric_potential> const signal_steady_offset_grnd_
)
: laser_modulation_frequency( laser_modulation_frequency_ ),
  monochrometer_wavelength( monochrometer_wavelength_),
  signal_phase( signal_phase_),
  signal_amplitude( signal_amplitude_ ),
  reference_amplitude( reference_amplitude_ ),
    
  signals_averaged( signals_averaged_ ),
  signal_to_noise( signal_to_noise_ ),
  running_signal_to_noise( running_signal_to_noise_ ),
    
  laser_modulation_amplitude( laser_modulation_amplitude_ ),
  laser_modulation_offset( laser_modulation_offset_ ),
  laser_pulse_width( laser_pulse_width_ ),
    
  reference_argument( reference_argument_ ),
  reference_argument_um( reference_argument_um_ ),

  samples( samples_ ),
  measurement_time( measurement_time_ ),
    
  signal_steady_offset_grnd( signal_steady_offset_grnd_ )
{}


} // namespace
} // namespace
