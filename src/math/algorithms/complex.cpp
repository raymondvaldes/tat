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

#include "math/algorithms/complex.h"

namespace math{ namespace algorithms{

vector<double> cmplx_split_real( const vector< complex<double> > &input)
{
  const size_t size = input.size();
  vector<double> output( size );
  
  for( size_t i = 0; i < size ; ++i  )
    output[i] = input[i].real() ;

  return output;
}

vector<double> cmplx_split_imag( const vector< complex<double> > &input)
{
  const size_t size = input.size();
  vector<double> output( size );
  
  for( size_t i = 0; i < size ; ++i  )
    output[i] = input[i].imag() ;

  return output;
}

double cmplx_modulus( const std::complex<double> &input )
{
  const double real = input.real();
  const double imag = input.imag();
  
  using std::sqrt;
  using std::pow;
  const double output = sqrt( pow( real,2 ) + pow( imag, 2) );

  return output;
}

std::complex<double> mod_phase_to_cmplx( const double mod, const double arg )
{
  using std::complex;
  using std::exp;
  const complex<double> _I_(0.,1.);
  complex<double> output(0.,0.);
  
  output = mod * exp( _I_ * arg ) ;

  return output;
}




}}