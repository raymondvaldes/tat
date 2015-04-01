/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "thermal/define/omega.h"
#include "sensible/layer.h"
#include <cmath>

using std::pow;

namespace thermal{
namespace define{

double omega( const double L_coat, const double l_thermal, const double k_c,
             const double psi_c ) noexcept
{
  return ( k_c / psi_c ) / ( pow( L_coat * l_thermal , 2 ) );
}
  
} // namespace define
} // namespace thermal
