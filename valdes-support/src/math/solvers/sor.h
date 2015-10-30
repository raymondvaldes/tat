/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__sor__
#define __tat__sor__

#include <iostream>

namespace math{namespace solvers{

double SOR( double**A, double*b, const size_t M2, double*phi, double omega,
            double error) noexcept;
            
}}
#endif /* defined(__tat__sor__) */
