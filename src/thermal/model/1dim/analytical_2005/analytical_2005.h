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

namespace thermal{ namespace model { namespace one_dim{
  
  using std::complex;
  
class analytical_2005
{
private:
  const double k_coat;
  const double psi_c;
  const double L_coat;
  const double I_intensity_ss;
  const double I_intensity_tt;

  const double Lambda;
  const double Temperature_interface;
  const double gamma;
  const double R1;
  const double Emit1;
  const double effusivity_sub;
  const std::complex<double> eye;


  double Lambda_hat ( const double lthermal ) const;
  complex<double> F_tilde( const double lthermal ) const;
  complex<double> eta ( const double Lambda_hat ) const;
  complex<double> M_tilde( const complex<double> x_in ) const;
  complex<double> N_tilde( const complex<double> x_in ) const;
  
          double  T_ss_R1eq1_eval( const double omega, const double z ) const ;
  complex<double> T_ts_R1eq1_eval( const double omega, const double z ) const ;

public:
  explicit analytical_2005( const double k_coat_in,
                            const double psi_c_in,
                            const double L_coat_in,
                            const double I_intensity_ss_in,
                            const double I_intensity_tt_in,
                            const double Lambda_in,
                            const double Temperature_interface_in,
                            const double gamma_in ,
                            const double R1_in ,
                            const double Emit1_in,
                            const double effusivity_sub_in ) ;
  ~analytical_2005( void ) ;
  
  complex<double> T_tt_eval_cplx( const double omega, const double z ) const;
  
  double phase_linear( const double omega1 ) ;
  double phase_nonlinear( const double omega ) ;

};
  
}}}
#endif /* defined(__tat_onedim_analytical_2005__) */