/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include <cmath>
#include "thermal/model/utilities/nondimensional/tau_0.h"

namespace thermal{namespace model{

double tau_0(const double omega) noexcept
{
  return ( 2. * M_PI ) / omega;
}


}}
