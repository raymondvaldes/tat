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
#include "math/utilities/even.h"

namespace gTBC {

namespace gMeasure {

using std::vector;
using std::string;
using std::pair;
using std::iota;
using std::make_pair;
using algorithm::for_each;
using algorithm::vector::reserve;

using algorithm::iota;
using tools::interface::import::columnData;

using units::quantity;
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
    string_to_quantity< dimensionless, double >( row[10] );
  
    auto const reference_argument  =
    string_to_quantity< plane_angle >( row[11], radians );
  
    auto const reference_argument_um =
    string_to_quantity< plane_angle >( row[12], radians );
    
    auto const samples =
    string_to_quantity< dimensionless, size_t >( row[13] );
  
    auto const measurement_time =
    string_to_quantity< time >( row[14], seconds );
  
    auto const signal_steady_offset_grnd =
    string_to_quantity< electric_potential >( row[15], volts );
  

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
noexcept -> meta_measurement_descriptions
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
  
  auto const output = meta_measurement_descriptions( descriptions );
  return output;
}

auto meta_measurement_descriptions::meta_laser_modulations(void) const
noexcept -> std::vector <
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > >
{
  auto results = vector< pair< quantity< frequency > , quantity< plane_angle >>>();

  for_each( meta_datas, [&results]( auto const & meta_data )
  {
    auto const laser_info = make_pair(  meta_data.laser_modulation_frequency,
                                        meta_data.reference_argument ) ;
    results.push_back( laser_info ) ;
  } ) ;

  return results;
}

auto meta_measurement_descriptions::meta_detector_grnds(void) const
noexcept -> std::vector < frequency_detector_ground >
{
  using math::utilities::is_even;
  
  auto const n_measurements = meta_datas.size();
  assert( is_even( n_measurements ) );
  
  auto results = vector< frequency_detector_ground >();
  results.reserve( meta_datas.size() / 2 ) ;
  
  for( size_t i = 0 ; i < meta_datas.size() ; ++i )
  {
    if( is_even(i+1) && i > 0 )
    {
      auto const f1 = meta_datas[i-1].laser_modulation_frequency;
      auto const f2 = meta_datas[i].laser_modulation_frequency;
      
      assert( std::abs( f1.value() - f2.value() )  < 10e-4 ) ;
      
      auto const lamb1 = make_pair( meta_datas[i-1].monochrometer_wavelength,
                                    meta_datas[i-1].signal_steady_offset_grnd );
      auto const lamb2 = make_pair( meta_datas[i].monochrometer_wavelength,
                                    meta_datas[i].signal_steady_offset_grnd );
      
      auto const freq_det_grnd = f1 ;
      
      
      results.emplace_back( freq_det_grnd, lamb1, lamb2 ) ;
    }
  }

  return results;
}

  
} // namespace gMeasure
  
} // namespace gTBC
