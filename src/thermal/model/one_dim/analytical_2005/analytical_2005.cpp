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

using std::isnormal;

namespace thermal{ namespace model {namespace one_dim{
  
analytical_2005::analytical_2005(
  const sensible::layer &coating_in,
  const sensible::layer &substrate_in,
  const sensible::radiativeSysProp &radiative_prop_in,
  const thermal::equipment::Laser &laser_in,
  const double temp_in,
  const double gamma_in )
  :
  one_dim( coating_in, substrate_in, radiative_prop_in, laser_in, temp_in,
           gamma_in ), _i_ ( 0 , 1 ), SQRTi( std::sqrt( _i_ ) )
  {}
  
analytical_2005::~analytical_2005( void ) {}


complex<double> analytical_2005::F_tilde( const double lthermal ) const
{
  using std::sqrt;
  const complex<double> sqrtIdivLthermal = SQRTi / lthermal;

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
  
  const complex<double> eta_out = 1. - pow( Lambda_hat, 2 ) * _i_ ;
  return eta_out;
}

complex<double>
analytical_2005::M_tilde( const complex<double> x_in, const double l ) const
{
  BOOST_ASSERT(  l > 0 ) ;

  using std::sinh;
  using std::cosh;
  
  typedef complex<double> complexD ;
  const complexD SQRTi_div_l = SQRTi / l ;
  const complexD sinhSQRTi = sinh( SQRTi_div_l ) ;
  const complexD coshSQRTi = cosh( SQRTi_div_l ) ;
  const complexD gammaXcoshSQRTplusSinhSQRT = gamma * coshSQRTi + sinhSQRTi;
  const double sinh_1_div_lambda = sinh( 1 / coat.Lambda ) ;

  complexD M_x = 1 ;
  M_x -= x_in * sinhSQRTi / sinh_1_div_lambda ;
  M_x /= gammaXcoshSQRTplusSinhSQRT ;


  typedef const bool checkif ;
  checkif verySmallThermalPenetration = ( !isnormal( M_x.real() ) || !isnormal( M_x.imag() ) ) ;

  if( verySmallThermalPenetration ) {
    BOOST_ASSERT( sinhSQRTi == coshSQRTi ) ;
    const auto evaluate_Limit_of_M_tilde = [=](){
      return - x_in / ( sinh_1_div_lambda * ( 1. + gamma ) ) ;
    } ;
  
    M_x = evaluate_Limit_of_M_tilde() ;
  }
  
  BOOST_ASSERT( !isnan( M_x.imag() ) ) ;
  BOOST_ASSERT( !isnan( M_x.real() ) ) ;
  
  return M_x;
}

complex<double>
analytical_2005::N_tilde( const complex<double> x_in, const double l ) const
{
  using std::sinh;
  using std::cosh;
  
  typedef complex<double> complexD ;
  const complexD sinhSQRTi = sinh( SQRTi / l ) ;
  const complexD coshSQRTi = cosh( SQRTi / l ) ;
  const complexD gammaXcoshSQRTplusSinhSQRT = gamma * coshSQRTi + sinhSQRTi;
  const double cosh_1_div_lambda = cosh( 1 / coat.Lambda ) ;
  
  complex<double> N_x = 1;
  N_x -= x_in * coshSQRTi / cosh_1_div_lambda ;
  N_x /= gammaXcoshSQRTplusSinhSQRT ;
  
  
  typedef const bool checkif ;
  checkif verySmallThermalPenetration = ( !isnormal( N_x.real() ) || !isnormal( N_x.imag() ) ) ;

  if( verySmallThermalPenetration ) {
    BOOST_ASSERT( sinhSQRTi == coshSQRTi ) ;
    const auto evaluate_Limit_of_N_tilde = [=](){
      return - x_in / ( cosh_1_div_lambda * ( 1. + gamma ) ) ;
    } ;
  
    N_x = evaluate_Limit_of_N_tilde() ;
  }
  
  BOOST_ASSERT( !isnan( N_x.real() ) ) ;
  BOOST_ASSERT( !isnan( N_x.imag() ) ) ;
  
  
  
  return N_x;
}
  
double analytical_2005::T_ss_R1eq1_eval( const double z ) const
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
  const complex<double> sqrtEyedivL = sqrt( _i_ ) / lthermal_val;

  complex<double> 
  coeff = coat.L * I_intensity_tt * lthermal_val ;
  coeff /= coat.k * eta_val ;
  
  const complex<double>
    coeff1 = ( 1 - exp( -2 / coat.Lambda ) ) / sqrt( _i_ ) ;
  
  const complex<double>
    coeff2 = F_til * cosh( sqrtEyedivL * z ) - sinh( sqrtEyedivL * z );
  
  const complex<double>
    coeff3 = 2 * Lambdahat_val * exp ( -1 / coat.Lambda ) ;
  
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
  const complex<double> sqrtIdivL = sqrt( _i_ ) / ltherm ;

  complex<double>
  coeff = ( 1 - R1 ) * exp( -1 / coat.Lambda ) ;
  coeff*= coat.L * I_intensity_tt * ltherm ;
  coeff/= coat.k * eta_val ;
  

  const complex<double> coeff1 = exp( -1 / coat.Lambda )  / sqrt( _i_ ) ;
  const complex<double> coeff2 = F_tilde( ltherm ) * cosh( sqrtIdivL * z )
                                                   - sinh( sqrtIdivL * z ) ;
  const complex<double> coeff3 = exp( ( z - 1 ) / coat.Lambda ) ;
  
  complex<double>
    coeff4  = ( gamma + sqrt( _i_ ) * Lambda_hat_val ) * cosh( sqrtIdivL * z ) ;
    coeff4 /= gamma * cosh( sqrtIdivL ) - sinh( sqrtIdivL ) ;
  

  const complex<double>
    bracket = coeff1 * coeff2 + Lambda_hat_val * ( coeff3 - coeff4 ) ;

  const complex<double>
    output = T_tt_R1eq1_eval( omega, z ) + coeff * bracket ;

  
  return output;
}
  
double analytical_2005::phase_linear( const double omega ) const
{
  BOOST_ASSERT( omega > 0 ) ;

  /*See 2004 emission paper equation 19*/
  using std::exp;
  using thermal::define::lthermal;
  const double l = lthermal( coat.L, coat.k, coat.psi, omega ) ;
  const double Lambda = coat.Lambda;
  
  const complex<double> M = M_tilde( SQRTi * Lambda / l , l ) ;
  const complex<double> N = N_tilde( _i_ * Lambda * Lambda / l / l, l ) ;
  
  const double halflamb = -2 / Lambda ;
  const double exp2lambda = exp( halflamb ) ;
  const complex<double> A =  ( 1 + R1 ) * ( 1 - exp2lambda ) * M ;
  const complex<double> B =  ( 1 - R1 ) * ( 1 + exp2lambda ) * N ;
  
  const complex<double> t = A + B;
  const complex<double> u  = 2. * ( 1. - Lambda * Lambda / l / l * _i_ ) ;
  const complex<double> v = Emit1 * SQRTi / l - 4 * gamma ;
  const double R1xExp2lambdaPLUS1 = std::fma( -R1, exp2lambda, 1 );
  
  using std::arg;
  const double phase = arg( v/u*t + 4 * R1xExp2lambdaPLUS1 ) - M_PI_2;

  
  BOOST_ASSERT( !isnan( phase ) ) ;

  return phase ;
}

vector<double>
analytical_2005::sweep_phase_linear( const vector<double> &omega ) const
{
  const size_t NUM = omega.size() ;
  vector<double> results( NUM ) ;
  
  for( size_t n = 0 ; n < NUM ; ++n ) {
    results[ n ] = phase_linear( omega[n] ) ;
  }
  
  for( const auto val : results ) {
    BOOST_ASSERT( !isnan( val ) ) ;
  }
  
  return results;
}


math::algorithms::spline_cplx
analytical_2005::T_tt_R1eq1_cplx_sweep( const double omega ) const
{
  using std::vector;
  using math::range;
  /* This methods returns a spline to the complex temperature field for the
     coating based on the laser harmonic modulation. */
  
  constexpr size_t pts= 500;
  constexpr double z_surf = 0;
  constexpr double z_interface = 1;
  const vector<double> z_values = range( z_surf, z_interface, pts ) ;

  vector<complex<double>> temp_discrete( pts ) ;
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
