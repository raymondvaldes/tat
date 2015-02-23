//
//  calculateCalibrationCoefficients.cpp
//  tat
//
//  Created by Raymond Valdes_New on 2/17/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/calculateCalibrationCoefficients.h"
#include "tools/interface/import/columnData.h"
#include "thermal/emission/signal.h"
#include "thermal/emission/spectrum.h"
#include "thermal/pyrometry/twoColor/calibrationGenerator.h"
#include "algorithm/vector/stringToQuantity.h"
#include "algorithm/vector/fill_with_list_values_as_constructor_arg.h"

namespace investigations {

namespace twoColorPyrometery {

inline void get_file_and_Import_Data(void){};
inline void calculate_calibration_coefficients(void){};
inline void output_Vectors_With_calibration_Coefficients(void){};

auto calculateCalibrationCoefficients( filesystem::directory const & dir )
-> void
{
  get_file_and_Import_Data();
    using algorithm::vector::fill_with_list_values_as_constructor_arg;
    using units::quantity;
    using units::si::length;
    using units::si::micrometers;
    using units::si::volts;
    using units::si::electric_potential;
    using units::si::wavelength;
    namespace celsius = units::celsius;
  
    using algorithm::vector::stringToQuantity;
    using tools::interface::import::columnData;
    using thermal::pyrometry::twoColor::calibrationGenerator;
    using thermal::emission::Signal;
    using thermal::emission::Spectrum;
    using std::for_each;
    using std::vector;

    auto const myParentPath = dir.parent_path() ;
    auto const myPath = myParentPath.pwd() + "/calibration/" + "blackBody.txt";
    
    auto const myData = columnData( myPath, "," ) ;
  
    auto const firstColumn = 1;
    auto const secondColumn = 2;
  
    auto const myWavelengths = stringToQuantity< length >(
      myData.getColumn( firstColumn ) , micrometers ) ;
    auto const myEmission200C = stringToQuantity< electric_potential >(
      myData.getColumn( secondColumn ) , volts ) ;
  
    auto const emissionTemperature =  200 * celsius::degrees() ;


    auto const signals = fill_with_list_values_as_constructor_arg <
      Signal< electric_potential > >( myWavelengths, myEmission200C ) ;
    auto const delta_lambda = quantity< wavelength >( 1.0 * micrometers ) ;

 // calculate_calibration_coefficients();
  //{
    auto const emission_spectrum = Spectrum<electric_potential>( signals, emissionTemperature ) ;
    auto const cGenerator = calibrationGenerator<electric_potential>( emission_spectrum );
    auto const coefficients = cGenerator.coefficientsAt( delta_lambda );
  
  
  
  
  
//    auto myEmission250C = stringToQuantity< electric_potential >( myData.getColumn( 3 ) , volts) ;
//    auto myEmission300C = stringToQuantity< electric_potential >( myData.getColumn( 4 ) , volts) ;
//    auto myEmission350C = stringToQuantity< electric_potential >( myData.getColumn( 5 ) , volts) ;
  
  
  
  
  //}
  
  
  
  output_Vectors_With_calibration_Coefficients();
  {
  
  }
}

} // namespace twoColorPyrometery
  
} // namespace investigations
