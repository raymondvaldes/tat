//
//  import_sweep_meta_data.h
//  tat
//
//  Created by Raymond Valdes_New on 3/18/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__import_sweep_meta_data__
#define __tat__import_sweep_meta_data__

#include "tools/interface/filesystem.hpp"
#include "units.h"

namespace gTBC {

namespace gMeasure {

struct meta_measurement_description{

  units::quantity< units::si::frequency>  laser_modulation_frequency;
  units::quantity< units::si::wavelength> monochrometer_wavelength;
  
  units::quantity< units::si::plane_angle>  signal_phase;
  units::quantity< units::si::electric_potential> signal_amplitude;
  units::quantity< units::si::dimensionless > reference_amplitude;
  
  units::quantity< units::si::dimensionless, size_t>  signals_averaged;
  units::quantity< units::si::dimensionless>  signal_to_noise;
  units::quantity< units::si::dimensionless>  running_signal_to_noise;
  
  units::quantity< units::si::dimensionless> laser_modulation_amplitude;
  units::quantity< units::si::dimensionless> laser_modulation_offset;
  units::quantity< units::si::dimensionless> laser_pulse_width;
  
  units::quantity< units::si::plane_angle> reference_argument;
  units::quantity< units::si::plane_angle> reference_argument_um;

  units::quantity< units::si::dimensionless, size_t> samples;
  units::quantity< units::si::time> measurement_time;
  
  units::quantity< units::si::electric_potential> signal_steady_offset_grnd;

  meta_measurement_description
  (
    units::quantity< units::si::frequency> const laser_modulation_frequency,
    units::quantity< units::si::wavelength> const monochrometer_wavelength,
    
    units::quantity< units::si::plane_angle> const signal_phase,
    units::quantity< units::si::electric_potential> const signal_amplitude,
    units::quantity< units::si::dimensionless > const reference_amplitude,

    units::quantity< units::si::dimensionless, size_t> const signals_averaged,
    units::quantity< units::si::dimensionless> const signal_to_noise,
    units::quantity< units::si::dimensionless> const running_signal_to_noise,
   
    units::quantity< units::si::dimensionless> const laser_modulation_amplitude,
    units::quantity< units::si::dimensionless> const laser_modulation_offset,
    units::quantity< units::si::dimensionless> const laser_pulse_width,
    
    units::quantity< units::si::plane_angle> const reference_argument,
    units::quantity< units::si::plane_angle> const reference_argument_um,

    units::quantity< units::si::dimensionless, size_t> const samples,
    units::quantity< units::si::time> const measurement_time,
    
    units::quantity< units::si::electric_potential> const signal_steady_offset_grnd
  );

};

auto
import_sweep_meta_data( filesystem::path const & path )
noexcept -> std::vector< meta_measurement_description >;

  
} // namespace gMeasure
  
} // namespace gTBC

#endif /* defined(__tat__import_sweep_meta_data__) */
