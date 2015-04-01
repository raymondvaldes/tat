/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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
