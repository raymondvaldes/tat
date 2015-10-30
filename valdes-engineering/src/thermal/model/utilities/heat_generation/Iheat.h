/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__Iheat__
#define __tat__Iheat__

#include <iostream>

namespace thermal{
namespace model{

double Iheat(double Isteady, double Itransient, double omega, double t) noexcept;

double Iheat_int(const double Isteady,const double Itransient,
                        const double omega, const double t) noexcept;


}}
#endif /* defined(__tat__Iheat__) */
