/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <cmath>
#include "Iheat.h"

namespace thermal{namespace model{

double Iheat(double Isteady, double Itransient, double omega, double t) noexcept
{
  using std::cos;
  return Isteady + Itransient * cos( omega * t )  ;
}

double Iheat_int(const double Isteady,const double Itransient,
                        const double omega, const double t) noexcept 
{
  using std::sin;
  return Isteady * t + ( Itransient * sin( omega * t ) ) / omega ;
}

}}
