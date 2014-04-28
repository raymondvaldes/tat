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

#ifndef __tat__numerical_2011__
#define __tat__numerical_2011__

#include <iostream>
#include <complex>
#include "math/algorithms/spline_cplx.h"
#include "thermal/model/one_dim/one_dim.h"

namespace thermal{ namespace model {namespace one_dim{

  using std::complex;
  using math::algorithms::spline_cplx;

class numerical_2011: protected one_dim
{
private:
          double  T_ss_R1eq1_eval( const double omega, const double z ) const ;
  complex<double> T_tt_R1eq1_eval( const double omega, const double z ) const ;

public:
  explicit numerical_2011( const sensible::layer &coating_in,
                           const sensible::radiativeSysProp &radiative_prop_in,
                           const thermal::equipment::Laser &laser_in,
                           const double temp_in,
                           const double gamma_in ) ;
  ~numerical_2011( void ) ;
  
  complex<double> T_tt_eval_cplx( const double omega, const double z ) const;
  double phase_linear( const double omega ) const ;
  double phase_nonlinear( const double omega ) const;
  
  //sweeps
  spline_cplx T_tt_R1eq1_cplx_sweep( const double omega ) const;
};

}}}

#endif /* defined(__tat__numerical_2011__) */
