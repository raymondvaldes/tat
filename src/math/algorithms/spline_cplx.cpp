/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "math/algorithms/spline_cplx.h"
#include "math/complex/container/get_real_component.h"
#include "math/complex/container/get_imag_component.h"

namespace math{ namespace algorithms {

using std::vector;
using std::complex;

using math::complex::container::get_real_component;
using math::complex::container::get_imag_component;

spline_cplx::spline_cplx( const vector< complex<double> > &ind,
                          const double* dep, const size_t c ) noexcept
  :real( dep, get_real_component( ind ).data() , c ),
   imag( dep, get_imag_component( ind ).data() , c )
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
