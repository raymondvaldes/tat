//
//  import_sweep_meta_data.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/18/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <numeric>

#include "import_sweep_meta_data.h"
#include "tools/interface/import/columnData.h"

#include "algorithm/algorithm.h"
#include "algorithm/vector/stringToQuantity.h"
#include "algorithm/vector/reserve.h"

namespace gTBC {

namespace gMeasure {

using std::vector;
using std::string;
using std::iota;
using algorithm::for_each;
using algorithm::vector::reserve;

using algorithm::iota;
using tools::interface::import::columnData;

using units::string_to_quantity;
using units::si::frequency;
using units::si::hertz;
using units::si::wavelength;
using units::si::micrometers;
using units::si::electric_potential;
using units::si::volts;
using units::si::millivolts;
using units::si::plane_angle;
using units::si::radians;
using units::si::dimensionless;
using units::si::time;
using units::si::seconds;

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

inline auto
strings_to_measurement_description( std::vector< std::string > const & row )
noexcept -> meta_measurement_description
{
    auto const laser_mod_freq =
    string_to_quantity< frequency >( row[0], hertz );
  
    auto const monochrometer_wavelength =
    string_to_quantity< wavelength >( row[1], micrometers );
    
    auto const signal_phase =
    string_to_quantity< plane_angle >( row[2], radians );
  
    auto const signal_amplitude =
    string_to_quantity< electric_potential >( row[3], millivolts );
  
    auto const reference_amplitude =
    string_to_quantity< dimensionless, double >( row[4] );
    
    auto const signals_averaged =
    string_to_quantity< dimensionless, size_t >( row[5] );
  
    auto const signal_to_noise =
    string_to_quantity< dimensionless, double >( row[6] );
  
    auto const running_signal_to_noise =
    string_to_quantity< dimensionless, double >( row[7] );
    
    auto const laser_modulation_amplitude =
    string_to_quantity< dimensionless, double >( row[8] );
  
    auto const laser_modulation_offset =
    string_to_quantity< dimensionless, double >( row[9] );
  
    auto const laser_pulse_width =
    string_to_quantity< dimensionless, double >( row[9] );
  
    auto const reference_argument  =
    string_to_quantity< plane_angle >( row[6], radians );
  
    auto const reference_argument_um =
    string_to_quantity< plane_angle >( row[7], radians );
    
    auto const samples =
    string_to_quantity< dimensionless, size_t >( row[8] );
  
    auto const measurement_time =
    string_to_quantity< time >( row[9], seconds );
  
    auto const signal_steady_offset_grnd =
    string_to_quantity< electric_potential >( row[9], volts );
  

    auto const meta_description = meta_measurement_description
    (
      laser_mod_freq,
      monochrometer_wavelength,
    
      signal_phase,
      signal_amplitude,
      reference_amplitude,
     
      signals_averaged,
      signal_to_noise,
      running_signal_to_noise,

      laser_modulation_amplitude,
      laser_modulation_offset,
      laser_pulse_width,
        
      reference_argument,
      reference_argument_um,
          
      samples,
      measurement_time,
      signal_steady_offset_grnd
    );

  return meta_description;
}

auto
import_sweep_meta_data( filesystem::path const & path )
noexcept -> std::vector< meta_measurement_description >
{
  auto const data = columnData( path.string(), { "*","#" } );

  auto const dimensions = data.size();
  auto const number_rows = dimensions.rows;
  
  auto rows = vector<vector<string>>();
  for( size_t i = 1 ; i <= number_rows ; ++i )
  {
    auto const each_row = data.getRow(i);
    
    rows.push_back( data.getRow(i) );
  }
  
  auto descriptions = vector< meta_measurement_description >();
  
  for_each( rows, [&descriptions]( auto const & row ) noexcept
  {
    auto const meta_description = strings_to_measurement_description( row );
    descriptions.push_back( meta_description );
  } );
  
  return descriptions;
}
  
} // namespace gMeasure
  
} // namespace gTBC
