/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "sensible/radiativeSysProp.h"

namespace sensible{
  
  
  


radiativeSysProp::
radiativeSysProp( const double R0_, const double R1_, const double Emit1_) noexcept
: R0(R0_), R1(R1_), Emit1(Emit1_){}

radiativeSysProp::
~radiativeSysProp(void) noexcept{}

class radiativeSysProp
radiativeSysProp::loadConfig( const boost::property_tree::ptree pt ) noexcept
{
  const double R0_ = pt.get<double>("R0");
  const double R1_ = pt.get<double>("R1");
  const double Emit1_ = pt.get<double>("Emit1");
  
  radiativeSysProp Obj( R0_, R1_, Emit1_);
  
  return Obj;
}
  
  
}
