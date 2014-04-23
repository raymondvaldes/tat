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

namespace thermal{ namespace model {namespace one_dim{
  
analytical_2005::analytical_2005(
  const sensible::layer &coating_in,
  const sensible::radiativeSysProp &radiative_prop_in,
  const thermal::equipment::Laser &laser_in,
  const double temp_in,
  const double gamma_in )
  :
  coat( coating_in.kthermal.offset, coating_in.psithermal.offset,
        coating_in.depth, coating_in.opticalPenetration() ),
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
  const complex<double> rootIdivLthermal = std::sqrt( eye ) / lthermal;

  using std::sinh;
  using std::cosh;
  complex<double>
  out =          cosh( rootIdivLthermal ) + gamma * sinh( rootIdivLthermal);
  out /= gamma * cosh( rootIdivLthermal ) +         sinh( rootIdivLthermal);

  return out;
}

double analytical_2005::Lambda_hat ( const double lthermal ) const
{
  return coat.Lambda / lthermal ;
}

complex<double> analytical_2005::eta ( const double Lambda_hat ) const
{
  const complex<double> eta_out = 1. - std::pow( Lambda_hat, 2 ) * eye ;
  return eta_out;
}

complex<double>
analytical_2005::M_tilde( const std::complex<double> x_in ) const
{
  complex<double> output;
  return output;
}

complex<double>
analytical_2005::N_tilde( const std::complex<double> x_in ) const
{
  complex<double> output;
  return output;
}
  
double analytical_2005::T_ss_R1eq1_eval( const double omega,
                                         const double z ) const
{
  using std::exp;
  using std::sinh;
  using std::cosh;
  
  const double coeff = 2 * coat.L * I_intensity_ss / coat.k ;
  
  double
  bracket = 1 - cosh( ( 1 - z ) / coat.Lambda ) ;
  bracket *= coat.Lambda;
  bracket += ( 1 - z ) * sinh( 1 / coat.Lambda ) ;
  
  const double
  output = coeff * exp( 1 / coat.Lambda ) * bracket + Temperature_interface;
  
  return output;
}

complex<double> analytical_2005::
  T_ts_R1eq1_eval( const double omega, const double z ) const
{
  using thermal::define::lthermal;
  const double lthermal_val = lthermal( coat.L, coat.k, coat.psi, omega ) ;
  const double Lambdahat_val = Lambda_hat ( lthermal_val ) ;
 
  const complex<double> F_til = F_tilde( lthermal_val ) ;
  const complex<double> eta_val = eta( Lambdahat_val ) ;
  
  using std::sqrt;
  const complex<double> sqrtEyedivL = sqrt( eye ) / lthermal_val;
  
  
  complex<double> 
  coeff = coat.L * I_intensity_tt * lthermal_val ;
  coeff /= coat.k * eta_val ;
  
  using std::exp;
  const complex<double>
    coeff1 = ( 1 - exp( -2 / coat.Lambda ) ) / sqrt( eye ) ;
  
  const complex<double>
    coeff2 = F_til * cosh( sqrtEyedivL * z ) - sinh( sqrtEyedivL * z );
  
  const complex<double>
    coeff3 = 2 * Lambdahat_val * exp ( -1 / Lambdahat_val ) ;
  
  complex<double>
  coeff4 =  gamma * cosh( sqrtEyedivL * z ) ;
  coeff4 /= gamma * cosh( sqrtEyedivL ) + sinh( sqrtEyedivL ) ;
  coeff4 -= cosh( ( 1 - z )  / coat.Lambda ) ;
  
  
  const complex<double> bracket = coeff1 * coeff2 - coeff3 * coeff4;
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
  
  complex<double>
  coeff = ( 1 - R1 ) * exp( -1 / coat.Lambda ) ;
  coeff*= ( coat.L * I_intensity_tt * ltherm);
  coeff/= coat.k * eta_val ;
  

  const complex<double> sqrtIdivL = sqrt( eye ) / ltherm ;
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
    output = T_ts_R1eq1_eval( omega, z ) + coeff * bracket ;
  
  return output;
}
  
double analytical_2005::phase_linear( const double omega )
{
  using thermal::define::lthermal;
  const double l = lthermal( coat.L, coat.k, coat.psi, omega ) ;
  const double Lambda = coat.Lambda;
  /*See 2004 emission paper equation 19*/

  constexpr complex<double> _i_ ( 0.0 , 1.0 ) ;
  const complex<double> SQRTi = std::sqrt(_i_);
  complex<double> M = 1;
  complex<double> N = 1;
  
  {
    using std::sinh;
    using std::cosh;
    
    const complex<double> sinhSQRTi = sinh( SQRTi / l ) ;
    const complex<double> coshSQRTi = cosh( SQRTi / l ) ;
    const complex<double>
      gammaXcoshSQRTplusSinhSQRT = gamma * coshSQRTi + sinhSQRTi;
    
    M -= SQRTi * Lambda / l * sinhSQRTi / sinh( 1 / Lambda ) ;
    M /= gammaXcoshSQRTplusSinhSQRT ;
    
    N -= _i_ * Lambda * Lambda / l / l * coshSQRTi / cosh( 1 / Lambda ) ;
    N /= gammaXcoshSQRTplusSinhSQRT ;
  }
  
  using std::exp;
  const double exp2lambda = exp( -2 / Lambda ) ;
  complex<double>
  A =  1 + R1 ;
  A *= 1 - exp2lambda;
  A *= M;
  
  complex<double>
  B =  1 - R1 ;
  B *= 1 + exp2lambda ;
  B *= N;
  
  const complex<double> t = A + B;
  const complex<double> u  = 2. * ( 1. - Lambda * Lambda / l / l * _i_ ) ;
  const complex<double> v = Emit1 * SQRTi / l - 4 * gamma ;
  const double R1xExp2lambdaPLUS1 = std::fma( -R1, exp2lambda, 1 );
  
  return std::arg( v/u*t + 4 * R1xExp2lambdaPLUS1 ) - M_PI_2 ;
}
  
  
  
  
}}}
