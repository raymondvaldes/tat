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
#include "statistics/signal_processing/average.h"
#include <algorithm> 
#include "algorithm/algorithm.h"
#include <valarray>

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
-> units::quantity< units::si::dimensionless >
{

  get_file_and_Import_Data();
    using algorithm::vector::fill_with_list_values_as_constructor_arg;
    using units::quantity;
    using units::si::length;
    using units::si::micrometers;
    using units::si::volts;
    using units::si::electric_potential;
    using units::si::wavelength;
    using units::si::dimensionless;
    namespace celsius = units::celsius;
  
    using algorithm::vector::stringToQuantity;
    using tools::interface::import::columnData;
    using thermal::pyrometry::twoColor::calibrationGenerator;
    using thermal::emission::Signal;
    using thermal::emission::Spectrum;
    using std::for_each;
    using std::vector;
    using algorithm::for_each;

    auto const wavelengthColumn = 1;

    auto const delta_lambda = quantity< wavelength >( 1.0 * micrometers ) ;
    auto const wavelength_offset = quantity< wavelength >( -.5743693 * micrometers );

      auto const myParentPath = dir.parent_path() ;
    auto const myPathNew = myParentPath.pwd() + "/calibration/" + "graphite_4_6_5_6.txt";

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
  


  
      auto const c2 = evaluateRawData( 2, 431 * celsius::degrees(), myPathNew );
      auto const c3 = evaluateRawData( 3, 518 * celsius::degrees(), myPathNew );
      auto const c4 = evaluateRawData( 4, 610 * celsius::degrees(), myPathNew );
      auto const c5 = evaluateRawData( 5, 470.9 * celsius::degrees(), myPathNew );

     // auto const c6 = evaluateRawData( 6, 470.0 * celsius::degrees(), myPathNew );
     // auto const c7 = evaluateRawData( 7, 321.2 * celsius::degrees(), myPathNew );
//      auto const c8 = evaluateRawData( 8, 350 * celsius::degrees(), myPathNew );
//      auto const c9 = evaluateRawData( 9, 375 * celsius::degrees(), myPathNew );
//      auto const c10 = evaluateRawData( 10, 700 * celsius::degrees(), myPathNew );
//      auto const c11 = evaluateRawData( 11, 800 * celsius::degrees(), myPathNew );
//      auto const c12 = evaluateRawData( 12, 900 * celsius::degrees(), myPathNew );
//      auto const c13 = evaluateRawData( 13, 1000 * celsius::degrees(), myPathNew );
//      auto const c14 = evaluateRawData( 14, 1100 * celsius::degrees(), myPathNew );
//      auto const c15 = evaluateRawData( 15, 1200 * celsius::degrees(), myPathNew );
    
//      auto i = 0;
//      std::for_each( c2.begin(), c2.end(), [&]( auto const & val )
//      {
//        std::cout <<  c2[i].second.value() << "\t" <<
//                      c3[i].second.value() << "\t" <<
//                      c4[i].second.value() << "\t" <<
//                      c5[i].second.value() << "\t" <<
//                      c6[i].second.value() << "\t" <<
//                      c7[i].second.value() << "\t" <<
//                      c8[i].second.value() << "\t" <<
//                      c9[i].second.value() << "\t" ;
////                      c10[i].second.value() << "\t" <<
////                      c11[i].second.value() << "\t" <<
////                      c12[i].second.value() << "\t" <<
////                      c13[i].second.value() << "\t" ;
////                      c14[i].second.value() << "\t" <<
////                      c15[i].second.value() ;
//                      std::cout << "\n";
//                ++i;
//      } );


    const vector< quantity< dimensionless > > gCoefficients {
    c2[0].second, c3[0].second, c4[0].second, c5[0].second
//    c5[0].second,
//      c6[0].second,
//      c7[0].second,
   // c8[0].second, c9[0].second
    };
  
    for_each( gCoefficients, []( auto const & g )
    {
      std::cout << g <<"\n";
    } );
  
  
    using statistics::signal_processing::average;
    auto const g_average = average( gCoefficients );
    return g_average;
  
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
