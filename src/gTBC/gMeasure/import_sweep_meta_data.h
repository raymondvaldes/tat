//
//  import_sweep_meta_data.h
//  tat
//
//  Created by Raymond Valdes_New on 3/18/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__import_sweep_meta_data__
#define __tat__import_sweep_meta_data__

#include <vector>
#include "tools/interface/filesystem.hpp"
#include "units.h"

namespace gTBC {
namespace gMeasure {

struct frequency_detector_ground{

  units::quantity< units::si::frequency > laser_frequency;
  
  std::pair<  units::quantity< units::si::wavelength >,
              units::quantity< units::si::electric_potential > > lambda1_grnd;
  
  std::pair<  units::quantity< units::si::wavelength >,
              units::quantity< units::si::electric_potential > > lambda2_grnd;
  
  frequency_detector_ground(
    units::quantity< units::si::frequency > const laser_frequency_,
    std::pair<  units::quantity< units::si::wavelength >,
              units::quantity< units::si::electric_potential > >
              const lambda1_grnd_,
    std::pair<  units::quantity< units::si::wavelength >,
              units::quantity< units::si::electric_potential > >
              const lambda2_grnd_
    ): laser_frequency( laser_frequency_ ),
      lambda1_grnd( lambda1_grnd_ ),
      lambda2_grnd( lambda2_grnd_ )  {};
};

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

struct meta_measurement_descriptions{

private:
  std::vector< meta_measurement_description > meta_datas;

public:
  meta_measurement_descriptions
  (
    std::vector< meta_measurement_description > meta_datas_
  ): meta_datas( meta_datas_ ){};
  
  auto laser_phases(void) const
  noexcept -> std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > >;
  
  auto laser_frequencies( void ) const
  noexcept -> std::vector< units::quantity< units::si::frequency > >;
  
  auto detector_grounds(void) const
  noexcept -> std::vector < frequency_detector_ground > ;

  auto measurement_amplitudes_1( void )
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;
  
  auto measurement_amplitudes_2( void )
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;
  
  auto measurement_amplitudes_average( void )
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;

  auto measurement_phases_1( void )
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;
  
  auto measurement_phases_2( void )
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;
  
  auto measurement_phases_average( void )
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;

  auto detector_wavelengths( void )
  noexcept -> std::pair<  units::quantity< units::si::wavelength >,
                          units::quantity< units::si::wavelength > >;
  
  auto is_twoColor_measurement( void ) noexcept -> bool;
  
  auto modulator_settings( void ) noexcept -> std::pair<
    units::quantity< units::si::dimensionless>,
    units::quantity< units::si::dimensionless> >;
};


auto
import_sweep_meta_data( filesystem::path const & path )
noexcept -> meta_measurement_descriptions;

} // namespace gMeasure
} // namespace gTBC

#endif /* defined(__tat__import_sweep_meta_data__) */
