//
//  pyrometery_settings_file.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//


#include "thermal/pyrometry/twoColor/pyrometery_settings_file.h"
#include "tools/interface/xml.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {

using std::string;
using std::make_pair;

using tools::interface::getTreefromFile;
using tools::interface::getItem;
using units::quantity;
using units::si::electric_potential;
using units::si::wavelength;
using units::si::micrometers;
using units::si::microvolts;
using units::si::volts;
using units::si::dimensionless;
using units::si::frequency;
using units::si::hertz;

using std::make_pair;

auto pyrometery_settings_file( filesystem::path const & fullpath ) -> Measurement_settings
{
  //// get my tree
  
  auto const pt = getTreefromFile( fullpath.string() ) ;
  auto const conjunto = string{"temperature_measurement."};
  auto const settings_branch = pt.get_child( conjunto + "settings" );

  auto const wavelength1_value  = settings_branch.get<double>( "wavelength1_nominal" );
  auto const wavelength1_nom = quantity<wavelength> ( wavelength1_value  * micrometers ) ;
  
  
  auto const wavelength2_value  = settings_branch.get<double>( "wavelength2_nominal" );
  auto const wavelength2_nom = quantity<wavelength> ( wavelength2_value  * micrometers ) ;
  
  auto const signalDC1_raw_value  = settings_branch.get<double>( "signal_DC_1" );
  auto const signalDC1_raw = quantity<electric_potential> ( signalDC1_raw_value  * volts ) ;
  
  auto const signalDC2_raw_value  = settings_branch.get<double>( "signal_DC_2" );
  auto const signalDC2_raw = quantity<electric_potential> ( signalDC2_raw_value  * volts ) ;


  auto const gCoeff_value  = settings_branch.get<double>( "calibration_coefficient" );
  auto const gCoeff = quantity<dimensionless> ( gCoeff_value ) ;

  auto const frequency_value  = settings_branch.get<double>( "frequency" );
  auto const temperoralFrequency = quantity<frequency> ( frequency_value  * hertz ) ;
  
  auto const cycles  = settings_branch.get<size_t>( "count" );

  auto const filename_1  = settings_branch.get<std::string>( "file1" );
  auto const filename_2  = settings_branch.get<std::string>( "file2" );
  
  auto const signal_DC_1 = make_pair( wavelength1_nom, signalDC1_raw ) ;
  auto const signal_DC_2 = make_pair( wavelength2_nom, signalDC2_raw ) ;

  auto const signalBackground_value  = settings_branch.get<double>( "signal_background" );
  auto const signalBackground = quantity<electric_potential> ( signalBackground_value  * volts ) ;

  auto const wavelength_offset_value  = settings_branch.get<double>( "wavelenth_offset" );
  auto const wavelength_offset = quantity<wavelength> ( wavelength_offset_value  * micrometers ) ;
  
  
  auto const output = Measurement_settings(
    signal_DC_1,
    signal_DC_2,
    signalBackground,
    wavelength_offset,
    gCoeff,
    temperoralFrequency,
    cycles,
    filename_1,
    filename_2  );
  
  return output;
}
  
} // namespace twoColor
  
} // namespace pyrometry

} // namespace thermal
