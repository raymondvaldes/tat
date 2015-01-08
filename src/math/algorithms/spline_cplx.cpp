/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
 -------------------------------------------------------------------------------
 License
 This file is part of Thermal Analysis Toolbox.
 
 Thermal Analysis Toolbox is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or (at your
 option) any later version.
 
 Thermal Analysis Toolbox is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along with
 Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.
 
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
