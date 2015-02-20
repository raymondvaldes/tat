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

#include "algorithm/vector/stringToQuantity.h"

namespace investigations {

namespace twoColorPyrometery {

inline void get_file_and_Import_Data(void){};
inline void calculate_calibration_coefficients(void){};
inline void output_Vectors_With_calibration_Coefficients(void){};

auto calculateCalibrationCoefficients( filesystem::directory const & dir )
-> void
{
  get_file_and_Import_Data();
  {
    using units::si::length;
    using units::si::millimeters;
    using units::si::volts;
    using units::si::electric_potential;
    using algorithm::vector::stringToQuantity;
    using tools::interface::import::columnData;

    auto myParentPath = dir.parent_path() ;
    auto myPath = myParentPath.pwd() + "/calibration/" + "blackBody.txt";
    
    auto myData = columnData( myPath, "," ) ;
    auto N = myData.size();
    
    auto myWavelengths = stringToQuantity< length >( myData.getColumn( 1 ) , units::si::micrometers) ;
    auto myEmission200C = stringToQuantity< electric_potential >( myData.getColumn( 2 ) , volts ) ;
    
    
    using thermal::emission::Signal;
    using thermal::emission::Spectrum;
    using std::generate;
    
auto const myFirstSignal =
      thermal::emission::Signal<units::si::electric_potential>
      ( myWavelengths[0], myEmission200C[0] );

    using celcius = units::absolute<boost::units::celsius::temperature>;
    auto emissionTemperature =  200 * celcius() ;
    
    auto emissionTempKelvin = units::absolute_conv_C_to_K_type::convert( emissionTemperature ) ;

    auto signals = std::vector< Signal<units::si::electric_potential> >();
    signals.reserve(N);
    
    
    auto i = 0;
    std::for_each( myWavelengths.begin(), myWavelengths.end() ,
    [&]( auto const & val)
    {
      auto const mySignal =
      thermal::emission::Signal<units::si::electric_potential>
      ( myWavelengths[i], myEmission200C[i] );
      
      signals.push_back(mySignal);
      
      i++;
    });


    for( const auto& signal : signals )
      std::cout << signal << "\n";
  
  
   // auto const myEmissionSpecturm200 = Spectrum<electric_potential>( signals, emissionTempKelvin ) ;
    
    
//    
//    using std::for_each;
//    for_each(
//      begin( myEmissionSpecturm200.signals ),
//      end( myEmissionSpecturm200.signals ), []( auto& Element ){
//        std::cout << Element << "\n";
//    });


    
    
    

    


//    auto myEmission250C = stringToQuantity< electric_potential >( myData.getColumn( 3 ) , volts) ;
//    auto myEmission300C = stringToQuantity< electric_potential >( myData.getColumn( 4 ) , volts) ;
//    auto myEmission350C = stringToQuantity< electric_potential >( myData.getColumn( 5 ) , volts) ;
//
//
//
//    
  }

  
  calculate_calibration_coefficients();
  {
  
  }
  
  output_Vectors_With_calibration_Coefficients();
  {
  
  }
}

} // namespace twoColorPyrometery
  
} // namespace investigations
