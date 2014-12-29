/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
-------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

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
