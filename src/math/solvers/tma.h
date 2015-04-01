/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__tma__
#define __tat__tma__

#include <iostream>
#include <vector>
#include <cstddef>

namespace math{namespace solvers{

void solveMatrix(const size_t n, const std::vector<double>& b,
                 const std::vector<double>& d, const std::vector<double>& a,
                 const std::vector<double>& C, std::vector<double>& u) noexcept;
}}
#endif /* defined(__tat__tma__) */
