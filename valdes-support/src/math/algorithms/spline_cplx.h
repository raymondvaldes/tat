/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__spline_cplx__
#define __tat__spline_cplx__

#include <iostream>
#include <vector>
#include <complex>
#include "math/algorithms/spline.h"

namespace math{ namespace algorithms {

class spline_cplx
{
private:
  mySpline real;
  mySpline imag;

public:
  explicit spline_cplx( const std::vector< std::complex<double> > &ind,
                        const double* dep, const size_t c ) noexcept;
 // ~spline_cplx( void ) ;
  std::complex<double> eval( const double xpos ) const noexcept;
};



}}

#endif /* defined(__tat__spline_cplx__) */
