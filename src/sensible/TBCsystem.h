/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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

#ifndef __tat__TBCsystem__sensible
#define __tat__TBCsystem__sensible

#include <iostream>
#include <boost/property_tree/ptree.hpp>

#include "sensible/temperature_scale.h"
#include "sensible/radiativeSysProp.h"
#include "sensible/layer.h"
#include "thermal/model/labels.h"

namespace sensible{
  
  using thermal::model::labels;
  
class TBCsystem
{
public:
  layer coating;
  layer truecoating;

  layer substrate;
  temperatureScale Temp;
  radiativeSysProp optical;
  
  double radius;
  double Rtc;
  double gamma;
  double a_sub;
  
    /// constructors and object creators
  explicit TBCsystem( const layer &coating_,
                      const layer &substrate_,
                      const temperatureScale &Temp_,
                      const radiativeSysProp &optical_,
                      const double radius_ ) noexcept;
  static TBCsystem loadConfig( const boost::property_tree::ptree &pt ) noexcept;
  ~TBCsystem(void) noexcept;
  
    /// Member operations that update on multiple members
  void updateVal( const enum labels::Name mylabel , const double val ) noexcept;
  double returnVal( const enum labels::Name mylabel ) const noexcept;
  
  double gammaEval( void ) const noexcept;
  double a_subEval( void ) const noexcept;
  void updateCoat( void ) noexcept;
};
  
}

#endif /* defined(__tat__TBCsystem__sensible) */