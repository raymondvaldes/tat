/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__radiativeSysProp__sensible
#define __tat__radiativeSysProp__sensible

#include <iostream>
#include <boost/property_tree/ptree.hpp>

namespace sensible{
  
class radiativeSysProp
{
private:
  
  
public:
  double R0;
  double R1;
  double Emit1;
  explicit radiativeSysProp( const double R0_, const double R1_,
                            const double Emit1_) noexcept;
  static radiativeSysProp
  loadConfig( const boost::property_tree::ptree pt ) noexcept;
  ~radiativeSysProp(void) noexcept;
};

}

#endif /* defined(__tat__radiativeSysProp__sensible) */
