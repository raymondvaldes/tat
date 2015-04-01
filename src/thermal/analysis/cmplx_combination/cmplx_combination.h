/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__cmplx_combination__
#define __tat__cmplx_combination__

#include <vector>
#include <complex>
#include <cstddef>
#include <utility>

#include <iostream>

namespace thermal{
namespace analysis{

std::vector<double>
Tcplx_to_Ttransient( const std::complex<double> &cplx , const double w,
                     const size_t res ) noexcept;

std::complex<double>
Ttransient_to_Tcplx( const std::vector<double>&Ttransient ) noexcept;
  
std::vector<double>
t_cmplx_to_t_time( const double omega, const double res ) noexcept;

}}

#endif /* defined(__tat__cmplx_combination__) */
