//
//  pyrometery_settings_file.h
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__pyrometery_settings_file__
#define __tat__pyrometery_settings_file__

#include <string>
#include <utility>

#include "tools/interface/filesystem.hpp"
#include "units.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {


struct Measurement_settings{

  std::pair<
    units::quantity< units::si::wavelength > ,
    units::quantity< units::si::electric_potential > > signal_DC_1 ;
  
  std::pair<
    units::quantity< units::si::wavelength > ,
    units::quantity< units::si::electric_potential > > signal_DC_2 ;

  units::quantity< units::si::electric_potential > signalBackground ;

  units::quantity< units::si::wavelength > wavelength_offset ;

  units::quantity< units::si::dimensionless > gCoeff;

  units::quantity< units::si::frequency > temperoralFrequency;
  
  size_t cycles;

  std::string filename_1;
  
  std::string filename_2;
  
  units::quantity< units::si::length > detector_view_radius;

  Measurement_settings
  (
  std::pair<
    units::quantity< units::si::wavelength > ,
    units::quantity< units::si::electric_potential > > const & signal_DC_1_ ,
  std::pair<
    units::quantity< units::si::wavelength > ,
    units::quantity< units::si::electric_potential > > const & signal_DC_2_ ,
  units::quantity< units::si::electric_potential > const & signalBackground_ ,
  units::quantity< units::si::wavelength > const & wavelength_offset_ ,
  units::quantity< units::si::dimensionless > const &gCoeff_,
  units::quantity< units::si::frequency > const & temperoralFrequency_,
  size_t const & cycles_,
  std::string const & filename_1_,
  std::string const & filename_2_,
  units::quantity< units::si::length > const detector_view_radius_
  )
  : signal_DC_1( signal_DC_1_ ),
    signal_DC_2( signal_DC_2_ ),
    signalBackground( signalBackground_ ),
    wavelength_offset( wavelength_offset_ ),
    gCoeff( gCoeff_ ),
    temperoralFrequency( temperoralFrequency_ ),
    cycles ( cycles_ ),
    filename_1 ( filename_1_ ),
    filename_2 ( filename_2_ ),
    detector_view_radius( detector_view_radius_ )
  {};
};

auto pyrometery_settings_file
(
  filesystem::path const & fullpath
)
-> Measurement_settings;

auto
pyrometery_settings_file
(
  filesystem::directory const & dir,
  std::string const & filename
)
-> Measurement_settings;

} // namespace twoColor
  
} // namespace pyrometry

} // namespace thermal

#endif /* defined(__tat__pyrometery_settings_file__) */
