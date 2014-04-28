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
#include <cmath>
#include "analytical_2005.h"
#include "thermal/define/lthermal.h"
#include "math/utility.hpp"

namespace thermal{ namespace model {namespace one_dim{
  
analytical_2005::analytical_2005(
  const sensible::layer &coating_in,
  const sensible::radiativeSysProp &radiative_prop_in,
  const thermal::equipment::Laser &laser_in,
  const double temp_in,
  const double gamma_in )
  :
  coat( coating_in.kthermal.offset, coating_in.psithermal.offset,
        coating_in.depth, coating_in.lambda ),
  I_intensity_ss(             laser_in.Is ),
  I_intensity_tt(             laser_in.It ),
  Temperature_interface(      temp_in ),
  gamma(                      gamma_in ),
  R1(                         radiative_prop_in.R1 ),
  Emit1(                      radiative_prop_in.Emit1 ),
  eye( 0.0,1.0 )
{}
  
analytical_2005::~analytical_2005( void ) {}


complex<double> analytical_2005::F_tilde( const double lthermal ) const
{
  using std::sqrt;
  const complex<double> sqrtIdivLthermal = sqrt( eye ) / lthermal;

  using std::sinh;
  using std::cosh;
  complex<double>
  out =          cosh( sqrtIdivLthermal ) + gamma * sinh( sqrtIdivLthermal);
  out /= gamma * cosh( sqrtIdivLthermal ) +         sinh( sqrtIdivLthermal);

  return out;
}

double analytical_2005::Lambda_hat ( const double lthermal ) const
{
  return coat.Lambda / lthermal ;
}

complex<double> analytical_2005::eta ( const double Lambda_hat ) const
{
  using std::pow;
  
  const complex<double> eta_out = 1. - pow( Lambda_hat, 2 ) * eye ;
  return eta_out;
}

complex<double>
analytical_2005::M_tilde( const complex<double> x_in, const double l ) const
{
  using std::sinh;
  using std::cosh;
  
  constexpr complex<double> _i_ ( 0.0 , 1.0 ) ;
  const complex<double> SQRTi = std::sqrt(_i_);
  
  
  const complex<double> sinhSQRTi = sinh( SQRTi / l ) ;
  const complex<double> coshSQRTi = cosh( SQRTi / l ) ;
  const complex<double>
  gammaXcoshSQRTplusSinhSQRT = gamma * coshSQRTi + sinhSQRTi;

  complex<double>
  M_x = 1;
  M_x -= x_in * sinhSQRTi / sinh( 1 / coat.Lambda ) ;
  M_x /= gammaXcoshSQRTplusSinhSQRT ;

  return M_x;
}

complex<double>
analytical_2005::N_tilde( const complex<double> x_in, const double l ) const
{
  using std::sinh;
  using std::cosh;
  
  constexpr complex<double> _i_ ( 0.0 , 1.0 ) ;
  const complex<double> SQRTi = std::sqrt(_i_);
  
  const complex<double> sinhSQRTi = sinh( SQRTi / l ) ;
  const complex<double> coshSQRTi = cosh( SQRTi / l ) ;
  const complex<double>
  gammaXcoshSQRTplusSinhSQRT = gamma * coshSQRTi + sinhSQRTi;
  
  complex<double> N_x = 1;
  N_x -= x_in * coshSQRTi / cosh( 1 / coat.Lambda ) ;
  N_x /= gammaXcoshSQRTplusSinhSQRT ;
  
  return N_x;
}
  
double analytical_2005::T_ss_R1eq1_eval( const double omega,
                                         const double z ) const
{
  using std::exp;
  using std::sinh;
  using std::cosh;
  
  const double coeff = 2 * coat.L * I_intensity_ss / coat.k ;
  
  double
  bracket = coat.Lambda ;
  bracket *= 1 - cosh( ( 1 - z ) / coat.Lambda ) ;
  bracket += ( 1 - z ) * sinh( 1 / coat.Lambda ) ;
  
  const double
  output = coeff * exp( -1 / coat.Lambda ) * bracket + Temperature_interface;
  
  return output;
}

complex<double> analytical_2005::
  T_tt_R1eq1_eval( const double omega, const double z ) const
{
  using std::sqrt;
  using std::exp;
  using std::sinh;
  using std::cosh;
  
  using thermal::define::lthermal;
  const double lthermal_val = lthermal( coat.L, coat.k, coat.psi, omega ) ;
  const double Lambdahat_val = Lambda_hat ( lthermal_val ) ;
 
  const complex<double> F_til = F_tilde( lthermal_val ) ;
  const complex<double> eta_val = eta( Lambdahat_val ) ;
  const complex<double> sqrtEyedivL = sqrt( eye ) / lthermal_val;
  
  
  complex<double> 
  coeff = coat.L * I_intensity_tt * lthermal_val ;
  coeff /= coat.k * eta_val ;
  
  const complex<double>
    coeff1 = ( 1 - exp( -2 / coat.Lambda ) ) / sqrt( eye ) ;
  
  const complex<double>
    coeff2 = F_til * cosh( sqrtEyedivL * z ) - sinh( sqrtEyedivL * z );
  
  const complex<double>
    coeff3 = 2 * Lambdahat_val * exp ( -1 / Lambdahat_val ) ;
  
  complex<double>
  coeff4 =  gamma * cosh( sqrtEyedivL * z ) ;
  coeff4 /= gamma * cosh( sqrtEyedivL ) + sinh( sqrtEyedivL ) ;
  coeff4 -= cosh( ( 1 - z ) / coat.Lambda ) ;
  
  
  const complex<double> bracket = coeff1 * coeff2 + coeff3 * coeff4;
  const complex<double> output = coeff * bracket;
  return output;
}


complex<double> analytical_2005::
  T_tt_eval_cplx( const double omega, const double z ) const
{
  using std::exp;
  using std::sqrt;
  using std::cosh;
  using std::sinh;
  using thermal::define::lthermal;
  
  const double ltherm = lthermal( coat.L, coat.k, coat.psi, omega ) ;
  const double Lambda_hat_val = Lambda_hat( ltherm ) ;
  const complex<double> eta_val = eta( Lambda_hat_val ) ;
  const complex<double> sqrtIdivL = sqrt( eye ) / ltherm ;

  complex<double>
  coeff = ( 1 - R1 ) * exp( -1 / coat.Lambda ) ;
  coeff*= coat.L * I_intensity_tt * ltherm ;
  coeff/= coat.k * eta_val ;
  

  const complex<double> coeff1 = exp( -1 / coat.Lambda )  / sqrt( eye ) ;
  const complex<double> coeff2 = F_tilde( ltherm ) * cosh( sqrtIdivL * z )
                                                   - sinh( sqrtIdivL * z ) ;
  const complex<double> coeff3 = exp( ( z - 1 ) / coat.Lambda ) ;
  
  complex<double>
    coeff4  = ( gamma + sqrt( eye ) * Lambda_hat_val ) * cosh( sqrtIdivL * z ) ;
    coeff4 /= gamma * cosh( sqrtIdivL ) - sinh( sqrtIdivL ) ;
  

  const complex<double>
    bracket = coeff1 * coeff2 + Lambda_hat_val * ( coeff3 - coeff4 ) ;

  const complex<double>
    output = T_tt_R1eq1_eval( omega, z ) + coeff * bracket ;
  
  return output;
}
  
double analytical_2005::phase_linear( const double omega ) const
{
  using thermal::define::lthermal;
  const double l = lthermal( coat.L, coat.k, coat.psi, omega ) ;
  const double Lambda = coat.Lambda;
  
  /*See 2004 emission paper equation 19*/

  constexpr complex<double> _i_ ( 0.0 , 1.0 ) ;
  const complex<double> SQRTi = std::sqrt(_i_);
  
  const complex<double> M = M_tilde( SQRTi * Lambda / l , l ) ;
  const complex<double> N = N_tilde( _i_ * Lambda * Lambda / l / l, l ) ;
  
  using std::exp;
  const double exp2lambda = exp( -2 / Lambda ) ;
  const complex<double> A =  ( 1 + R1 ) * ( 1 - exp2lambda ) * M ;
  const complex<double> B =  ( 1 - R1 ) * ( 1 + exp2lambda ) * N ;
  
  const complex<double> t = A + B;
  const complex<double> u  = 2. * ( 1. - Lambda * Lambda / l / l * _i_ ) ;
  const complex<double> v = Emit1 * SQRTi / l - 4 * gamma ;
  const double R1xExp2lambdaPLUS1 = std::fma( -R1, exp2lambda, 1 );
  
  using std::arg;
  const double phase = arg( v/u*t + 4 * R1xExp2lambdaPLUS1 ) - M_PI_2;
  
  return phase ;
}

math::algorithms::spline_cplx
analytical_2005::T_tt_R1eq1_cplx_sweep( const double omega) const
{
  using std::vector;
  using math::range;
  /* This methods returns a spline to the complex temperature field for the
     coating based on the laser harmonic modulation. */
  
  constexpr size_t pts= 500;
  constexpr double z_surf = 0;
  constexpr double z_interface = 1;
  const vector<double> z_values = range( z_surf, z_interface, pts ) ;

  

  vector<complex<double>> temp_discrete( pts );
  for( size_t i = 0 ; i < pts ; ++i )
  {
    temp_discrete[i] = T_tt_R1eq1_eval( omega, z_values[i] ) ;
  }

  using math::algorithms::spline_cplx ;
  spline_cplx temperature_field( temp_discrete, z_values.data(), pts ) ;
  
  return temperature_field;
}

  
double analytical_2005::phase_nonlinear( const double omega ) const
{
  /*Nonlinear emission field will be calculated based on the analytical 
   temperature field.  This should be very similar to the linear model for
   low temperatures fluctuations. */
  /* Step 1 create complex tempearture distribution */
  using math::range;
  
  const size_t resolution = 500;
  using std::vector;
  using std::complex;
  
  vector< complex<double> > temp_cplx( resolution ) ;
  const vector< double > z_pos = range( 0, 1, resolution ) ;
  
  for( size_t i = 0 ; i < resolution ; ++i )
  {
    temp_cplx[i] = T_tt_eval_cplx( omega, z_pos[i] ) ;
  }
  
  /* Step 2 evaluate complex temperature distribution for emission */
  
  
  
  
  
  
  /* Step 3 fit emission field over temperature distribution */
  
  
  
  
  
  
  double phase = 0;
  return phase;
}
  
  
  
  
}}}
