//
//  calculateCalibrationCoefficients.cpp
//  tat
//
//  Created by Raymond Valdes_New on 2/17/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>

#include "investigations/twoColorPyrometery/calculateCalibrationCoefficients.h"
#include "tools/interface/import/columnData.h"
#include "thermal/emission/signal.h"
#include "thermal/emission/spectrum.h"
#include "thermal/pyrometry/twoColor/calibrationGenerator.h"
#include "algorithm/vector/stringToQuantity.h"
#include "algorithm/vector/fill_with_list_values_as_constructor_arg.h"

#include <algorithm> 

namespace investigations {

namespace twoColorPyrometery {

inline void get_file_and_Import_Data(void){};
inline void calculate_calibration_coefficients(void){};
inline void output_Vectors_With_calibration_Coefficients(void){};

inline auto
calibrate_wavelength( units::quantity<units::si::wavelength> const & raw,
                      units::quantity<units::si::wavelength> const & offset )
noexcept-> units::quantity<units::si::wavelength>
{
  return raw + offset;
}

inline auto
calibrate_wavelengths(
  std::vector< units::quantity< units::si::wavelength > > const & raw,
  units::quantity<units::si::wavelength> const & offset )
noexcept-> std::vector< units::quantity< units::si::wavelength > >
{
  auto wavelengths = raw;
  
  using std::generate;
  using std::begin;
  using std::end;
  
  transform( begin( wavelengths ), end( wavelengths ), begin( wavelengths ),
  [&]( auto const & wavelength )
  {
    return calibrate_wavelength( wavelength, offset );
  } );

  return wavelengths;
}

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

    auto const wavelengthColumn = 1;

    auto const emmissionColumnVerification = 2;
    auto const emissionTemperatureVerification =  204.5 * celsius::degrees() ;
  
    auto const emmissionColumn2 = 2;
    auto const emissionTemperature200 =  200 * celsius::degrees() ;
  
    auto const emmissionColumn3 = 3 ;
    auto const emissionTemperature300 =  300 * celsius::degrees() ;

    auto const emmissionColumn4 = 4 ;
    auto const emissionTemperature400 =  400 * celsius::degrees() ;

    auto const emmissionColumn5 = 5 ;
    auto const emissionTemperature500 =  500 * celsius::degrees() ;
  
    auto const delta_lambda = quantity< wavelength >( 1.0 * micrometers ) ;
  //  auto const wavelength_offset = quantity< wavelength >( -.57412 * micrometers );
    auto const wavelength_offset = quantity< wavelength >( 0 * micrometers );

  
    auto const myParentPath = dir.parent_path() ;
    auto const myPathNew = myParentPath.pwd() + "/calibration/" + "blackBody.txt";
    auto const myPathVerification = myParentPath.pwd() + "/calibration/" + "blackBody_verifcation.txt";

    auto const evaluateRawData = [&]( auto const emmissionColumn,
                                      auto const emissionTemperature,
                                      auto const &myPath ) noexcept
    {
      auto const myData = columnData( myPath ) ;
    
      auto wavelengths_raw = stringToQuantity< length >(
        myData.getColumn( wavelengthColumn ) , micrometers ) ;
    
    
      auto const wavelengths = calibrate_wavelengths( wavelengths_raw, wavelength_offset ) ;
      auto const emissionSignal = stringToQuantity< electric_potential >(
        myData.getColumn( emmissionColumn ) , volts ) ;


      auto const signals = fill_with_list_values_as_constructor_arg <
        Signal< electric_potential > >( wavelengths, emissionSignal ) ;

      auto const emission_spectrum = Spectrum<electric_potential>( signals, emissionTemperature ) ;
      auto const cGenerator = calibrationGenerator<electric_potential>( emission_spectrum );
      auto const coefficients = cGenerator.coefficientsAt( delta_lambda );
      return coefficients;
    };
  

    {
      auto const c300 = evaluateRawData( emmissionColumn3, emissionTemperature300, myPathNew );
      auto const c400 = evaluateRawData( emmissionColumn4, emissionTemperature400, myPathNew );
      auto const c500 = evaluateRawData( emmissionColumn5, emissionTemperature500, myPathNew );
    
      auto i = 0;
      std::for_each( c300.begin(), c300.end(), [&]( const auto & val )
      {
        std::cout <<  c300[i].second.value() << "\t" <<
                      c400[i].second.value() <<"\t"<<
                      c500[i].second.value() << "\n";
        ++i;
      } );
    }






  
//      std::cout << "\n\n\n";
//    {
//      auto const coefficients = evaluateRawData( emmissionColumnVerification, emissionTemperatureVerification, myPathVerification );
//    
//      for( auto const & coeff : coefficients  )
//      {
//        std::cout << units::engineering_prefix;
//        std::cout << coeff.first.first << "\t" <<coeff.first.second << "\t";
//        std::cout << units::no_prefix << coeff.second << "\n";
//      }
//    }
//    

}

} // namespace twoColorPyrometery
  
} // namespace investigations
