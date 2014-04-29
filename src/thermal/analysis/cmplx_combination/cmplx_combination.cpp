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
#include <cassert>
#include <cmath>

#include "thermal/analysis/cmplx_combination/cmplx_combination.h"
#include "physics/classical_mechanics/kinematics.h"
#include "math/utility.hpp"
#include "math/estimation/cosfit.hpp"
#include "math/algorithms/complex.h"

namespace thermal{
namespace analysis{

std::vector<double>
Tcplx_to_Ttransient( const std::complex<double> &cplx , const double omega,
                     const size_t res )
{
  /* I need a function that takes a complex variable and outputs time.
      Input: complex
           angular frequency
           resolution
      Output: std::vector< doubles >
      
      T_transient(t) =  Re{ T_cmplx * exp( i * omega * time ) }
  */
  const std::complex<double> _I_(0,1);

  using physics::classical_mechanics::angularFrequency_to_period;
  const double period = angularFrequency_to_period( omega ) ;
  const std::vector<double> time = math::range(0, period, res);
  
  using std::arg;
  using std::exp;
  
  std::vector<double>output(res);
  for( size_t i = 1 ; i < res ; ++i )
    output[i] = arg( cplx + exp( _I_ * omega * time[i]  ) ) ;
  
 return output;
}

std::complex<double>
Ttransient_to_Tcplx( const std::vector<double> Ttransient ,
                     const std::vector<double> time )
{
  /* Only one period or wavelength of thermal transient temperature data can
     be sent as the arguement. This can be verified by using an assert */
  using std::abs;
  using std::complex;
  using std::pair;
  using math::OA_init ;
  
  //safety checks
  const double tol = Ttransient.front() * 0.001;
  assert( abs( Ttransient.front() - Ttransient.back() ) < tol ) ;
  
  //retrieve initial guess
  const double*Tptr = Ttransient.data();
  const size_t Tsize = Ttransient.size();
  const pair<double, double> OA_initial = OA_init( Tptr , Tsize ) ;

  const double offset_i = OA_initial.first;
  const double amplitude_i = OA_initial.second;
  const double phase_i = -M_PI_2;
  double OAP[3] = { offset_i, amplitude_i, phase_i } ;

  //best-fit cosine to get amplitude and phase
  using math::estimation::cosfit;
  cosfit( Tptr, time, OAP, Tsize ) ;
  
  const double mod_fitted = OAP[1];
  const double arg_fitted = OAP[2];
  
  //use phase, amplitude data to get back cmplx temperature field
  using math::algorithms::mod_phase_to_cmplx ;
  const complex<double> Tcplx = mod_phase_to_cmplx( mod_fitted, arg_fitted ) ;
  
  return Tcplx;
}

}}