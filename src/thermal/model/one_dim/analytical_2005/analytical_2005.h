/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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
