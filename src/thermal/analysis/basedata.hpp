/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef BASEDATA_HPP
#define BASEDATA_HPP

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/thermalData.hpp"

namespace thermal{
namespace analysis{

class baseData
{
public:
  std::shared_ptr< Kernal > coreSystem;
  std::shared_ptr< ThermalData > thermalData;
  std::shared_ptr< math::estimation::unknownList > unknownParameters;
  
  void updateObjects( const Kernal& coreSystemIn, const ThermalData& thermalDataIn,
               const math::estimation::unknownList& unknownParametersIn ) noexcept {
    using std::make_shared;
    
    coreSystem = make_shared< Kernal >( coreSystemIn ) ;
    thermalData = make_shared< ThermalData >( thermalDataIn ) ;
    unknownParameters = make_shared< math::estimation::unknownList >( unknownParametersIn ) ;
  };
  
  void assignPointer( const std::shared_ptr< math::estimation::unknownList > &list_in,
         const std::shared_ptr< ThermalData > &thermalData_in,
         const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) noexcept
  {
    unknownParameters = list_in ;
    thermalData = thermalData_in ;
    coreSystem = coreSystem_in ;
  };
};

}}

#endif // BASEDATA_HPP
