/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__temperature_scale__sensible
#define __tat__temperature_scale__sensible

#include <iostream>
#include <boost/property_tree/ptree.hpp>

namespace sensible{
  
  using std::string;

class temperatureScale
{
  
public:
  double tolerance;
  double referance;
  double base;
  double rear;
  
  explicit temperatureScale( const double tolerance_,const double referance_,
                             const double base_, const double rear_) noexcept;
  static temperatureScale
  loadConfigfromXML( const boost::property_tree::ptree pt ) noexcept;
  ~temperatureScale( void ) noexcept;
};
  
  
  
  
  
  
}

#endif /* defined(__tat__temperature_scale__sensible) */
