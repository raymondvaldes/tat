//
//  meta_measurement_description.hpp
//  tat
//
//  Created by Raymond Valdes on 10/13/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef meta_measurement_description_hpp_101315
#define meta_measurement_description_hpp_101315

#include "units.h"
#include "thermal/equipment/detector/periodic_signal_properties.hpp"
#include "thermal/equipment/detector/signal.h"

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
  
  auto get_periodic_signal_properties
  (
    thermal::equipment::detector::Signal signal_steady_offset
  ) const -> thermal::equipment::detector::periodic_signal_properties
  {
    using thermal::equipment::detector::periodic_signal_properties;
    
    auto const signal_frequency = laser_modulation_frequency;
    
    auto const output = periodic_signal_properties
    (
      signal_steady_offset,
      signal_amplitude,
      signal_frequency,
      signal_phase
    );
    
    return output;
  }

};


} // namespace gMeasure
} // namespace gTBC

#endif /* meta_measurement_description_hpp */
