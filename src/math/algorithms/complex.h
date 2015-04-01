/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__cmplx_split__
#define __tat__cmplx_split__

#include <iostream>
#include <vector>
#include <complex>

namespace math { namespace algorithms{

using std::vector;
using std::complex;

vector<double> cmplx_split_real( const vector< complex<double> > &input) noexcept;
vector<double> cmplx_split_imag( const vector< complex<double> > &input) noexcept;
double cmplx_modulus( const std::complex<double> &input ) noexcept;

std::complex<double>
mod_phase_to_cmplx( const double mod, const double phase ) noexcept;

}}

#endif /* defined(__tat__cmplx_split__) */
