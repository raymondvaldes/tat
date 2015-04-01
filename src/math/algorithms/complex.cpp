/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "math/algorithms/complex.h"

namespace math{ namespace algorithms{

vector<double> cmplx_split_real( const vector< complex<double> > &input) noexcept
{
  const size_t size = input.size();
  vector<double> output( size );
  
  for( size_t i = 0; i < size ; ++i  )
    output[i] = input[i].real() ;

  return output;
}

vector<double> cmplx_split_imag( const vector< complex<double> > &input) noexcept
{
  const size_t size = input.size();
  vector<double> output( size );
  
  for( size_t i = 0; i < size ; ++i  )
    output[i] = input[i].imag() ;

  return output;
}

double cmplx_modulus( const std::complex<double> &input ) noexcept
{
  const double real = input.real();
  const double imag = input.imag();
  
  using std::sqrt;
  using std::pow;
  const double output = sqrt( pow( real,2 ) + pow( imag, 2) );

  return output;
}

std::complex<double> mod_phase_to_cmplx( const double mod, const double arg ) noexcept
{
  using std::complex;
  using std::exp;
  const complex<double> _I_(0.,1.);
  complex<double> output(0.,0.);
  
  output = mod * exp( _I_ * arg ) ;

  return output;
}




}}
