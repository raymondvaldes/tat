/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <cassert>
#include <cmath>

#include "thermal/analysis/cmplx_combination/cmplx_combination.h"
#include "physics/classical_mechanics/kinematics.h"
#include "math/utility.hpp"
#include "math/estimation/cosfit.hpp"
#include "math/complex/mod_phase_to_complex.h"

namespace thermal{
namespace analysis{

std::vector<double>
Tcplx_to_Ttransient( const std::complex<double> &cplx , const double omega,
                     const size_t res ) noexcept
{
  using std::arg;
  using std::exp;
  using std::vector;
  using std::complex;
  const complex<double> _I_(0,1) ;
  
  /* I need a function that takes a complex variable and outputs time.
      Input: complex
           angular frequency
           resolution
      Output: std::vector< doubles >
      
      T_transient(t) =  Re{ T_cmplx * exp( i * omega * time ) }
  */
  const vector<double> time = t_cmplx_to_t_time( omega, res ) ;
  
  vector<double>output(res);
  for( size_t i = 0 ; i < res ; ++i )
    output[i] = real( cplx * exp( _I_ * omega * time[i]  ) ) ;
  
 return output;
}

std::complex<double>
Ttransient_to_Tcplx( const std::vector<double> & Ttransient ) noexcept
{
  /* Only one period or wavelength of thermal transient temperature data can
     be sent as the arguement. This can be verified by using an assert */
  using std::abs;
  using std::complex;
  using std::pair;
  using math::OA_init ;
  
  //safety checks
  const double tol = abs(Ttransient.front()) * 0.0001 ;
  const double convergence = abs( Ttransient.front() - Ttransient.back() ) ;
  const bool assertChkr = std::islessequal( convergence ,  tol ) ;  
  assert( assertChkr ) ;
  
  //retrieve initial guess
  const double* Tptr = Ttransient.data() ;
  const size_t Tsize = Ttransient.size() ;
  const pair<double, double> OA_initial = OA_init( Tptr , Tsize ) ;

  const double offset_i = OA_initial.first ;
  const double amplitude_i = OA_initial.second ;
  
  const double phase_i = -M_PI_2 ;
  double OAP[3] = { offset_i, amplitude_i, phase_i } ;

  //best-fit cosine to get amplitude and phase
  using math::estimation::cosfit ;

  const std::vector<double> time = math::range(0, 1, Tsize);
  cosfit( Tptr, time, OAP, Tsize ) ;
  
  const double mod_fitted = OAP[1] ;
  const double arg_fitted = OAP[2] ;
  
  //use phase, amplitude data to get back cmplx temperature field
  using math::complex::mod_phase_to_complex ;
  const complex<double> Tcplx = mod_phase_to_complex( mod_fitted, arg_fitted ) ;
  
  return Tcplx;
}

#include "math/utility.hpp"
std::vector<double>
t_cmplx_to_t_time( const double omega, const double res ) noexcept
{
  using physics::classical_mechanics::angularFrequency_to_period ;
  auto const period = angularFrequency_to_period( omega ) ;
  
  using std::lrint;
  const size_t increments = lrint( period / res);
  
  auto const time = math::range(0, period, increments) ;
  
  return time;

}


}}
