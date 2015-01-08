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

#ifndef __tat_onedim_analytical_2005__
#define __tat_onedim_analytical_2005__

#include <iostream>
#include <complex>
#include <vector>
#include "math/algorithms/spline_cplx.h"
#include "thermal/model/one_dim/one_dim.h"

namespace thermal{ namespace model { namespace one_dim{
  
  using std::complex;
  using std::vector;
  using math::algorithms::spline_cplx;
  
class analytical_2005: protected one_dim
{
private:
  const complex<double> _i_ ;
  const complex<double> SQRTi ;

  double Lambda_hat ( const double lthermal ) const noexcept;
  complex<double> F_tilde( const double lthermal ) const noexcept;
  complex<double> eta ( const double Lambda_hat ) const noexcept;
  complex<double> M_tilde( const complex<double> x_in, const double l ) const noexcept;
  complex<double> N_tilde( const complex<double> x_in, const double l ) const noexcept;
  
          double  T_ss_R1eq1_eval( const double z ) const noexcept;
  complex<double> T_tt_R1eq1_eval( const double omega, const double z ) const noexcept;

public:
  explicit analytical_2005( const sensible::layer &coating_in,
                            const sensible::layer &substrate_in,
                            const sensible::radiativeSysProp &radiative_prop_in,
                            const thermal::equipment::Laser &laser_in,
                            const double temp_in,
                            const double gamma_in ) noexcept;
  ~analytical_2005( void ) noexcept;
  
  complex<double> T_tt_eval_cplx( const double omega, const double z ) const noexcept;
  double phase_linear( const double omega ) const noexcept;
  double phase_nonlinear( const double omega ) const noexcept;
  
  vector<double>
  sweep_phase_linear( const vector<double> &omega ) const noexcept;


  //sweeps
  spline_cplx T_tt_R1eq1_cplx_sweep( const double omega ) const noexcept;
};
  
}}}
#endif /* defined(__tat_onedim_analytical_2005__) */
