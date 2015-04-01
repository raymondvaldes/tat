/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__temp_cmplx__
#define __tat__temp_cmplx__

#include <iostream>
#include <vector>
#include "thermal/analysis/kernal.hpp"

namespace thermal{
namespace analysis{
namespace sweep{

std::vector< std::complex<double> >
temp_cplx_99( const thermal::analysis::Kernal &popteaCore,
              const double omega , const size_t M1 ) noexcept;

}}}

#endif /* defined(__tat__temp_cmplx__) */
