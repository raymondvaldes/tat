/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "math/algorithms/spline_cplx.h"
#include "math/algorithms/complex.h"

namespace math{ namespace algorithms {

using std::vector;
using std::complex;


spline_cplx::spline_cplx( const vector< complex<double> > &ind,
                          const double* dep, const size_t c ) noexcept
  :real( dep, cmplx_split_real( ind ).data() , c ),
   imag( dep, cmplx_split_imag( ind ).data() , c )
{
}

complex<double>
spline_cplx::eval( const double xpos ) const noexcept
{
  const complex<double> output( real.eval(xpos), imag.eval(xpos) );
  return output;
}

//spline_cplx::~spline_cplx(void){}



}}
