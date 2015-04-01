/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/


#ifndef __tat__omega__
#define __tat__omega__

#include <iostream>

namespace thermal{
  namespace define{

double omega( const double L_coat, const double l_thermal, const double k_c,
              const double psi_c ) noexcept;

    
}}
#endif /* defined(__tat__omega__) */
