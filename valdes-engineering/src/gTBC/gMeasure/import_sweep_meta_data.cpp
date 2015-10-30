//
//  import_sweep_meta_data.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/18/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <numeric>
#include <stdexcept>

#include "import_sweep_meta_data.h"
#include "tools/interface/import/columnData.h"

#include "algorithm/algorithm.h"
#include "units/container/string_to_quantity.h"
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

using namespace units;

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
    string_to_quantity< si::time >( row[14], seconds );
  
    auto const steady_signal_double = -std::stod( row[15] );
  
    auto const signal_steady_offset_grnd =
    units::quantity< electric_potential >( steady_signal_double * volts);

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
-> meta_measurement_descriptions
{
  auto const data = columnData( path.string(), { "*","#" } );

  auto const dimensions = data.size();
  auto const number_rows = dimensions.rows;
  
  if( number_rows ==0 ) {
    throw std::domain_error( "*.TBD file is empty" );
  }
  
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



} // namespace gMeasure
} // namespace gTBC
