/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	           	|
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
#include <complex>
#include "thermal/model/1dim/analytical_2005/heat1dAna.h"
#include "thermal/define/lthermal.h"

namespace thermal {
namespace heat{

double PhaseOfEmission1DAna( const double omega1, const double L_coat,
                             const double k_c, const double psi_c,
                             const double lambda, const double R1,
                             const double gamma, const double Esigma )
{
  using thermal::define::lthermal;
  const double l = lthermal( L_coat , k_c , psi_c , omega1 ) ;
  
  /*See 2004 emission paper equation 19*/
  //  const double omega1 = omegas[flag];
  
  using std::complex;
  constexpr complex<double> _i_ ( 0.0 , 1.0 ) ;
  const complex<double> SQRTi = std::sqrt(_i_);
  complex<double> M = 1;
  complex<double> N = 1;
  
  {
    using std::sinh;
    using std::cosh;
  
    const complex<double> sinhSQRTi = sinh( SQRTi / l ) ;
    const complex<double> coshSQRTi = cosh( SQRTi / l ) ;
    const complex<double> gammaXcoshSQRTplusSinhSQRT = gamma * coshSQRTi + sinhSQRTi;
    
    M -= SQRTi * lambda / l * sinhSQRTi / sinh( 1 / lambda ) ;
    M /= gammaXcoshSQRTplusSinhSQRT ;
    
    N -= _i_ * lambda * lambda / l / l * coshSQRTi / cosh( 1 / lambda ) ;
    N /= gammaXcoshSQRTplusSinhSQRT ;
  }
  
  using std::exp;
  const double exp2lambda = exp( -2 / lambda ) ;
  complex<double>
  A =  1 + R1 ;
  A *= 1 - exp2lambda;
  A *= M;
  
  complex<double>
  B =  1 - R1 ;
  B *= 1 + exp2lambda ;
  B *= N;
  
  const complex<double> t = A + B;
  const complex<double> u  = 2. * ( 1. - lambda * lambda / l / l * _i_ ) ;
  const complex<double> v = Esigma * SQRTi / l - 4 * gamma ;
  const double R1xExp2lambdaPLUS1 = std::fma( -R1, exp2lambda, 1 );
  
  return std::arg( v/u*t + 4 * R1xExp2lambdaPLUS1 ) - M_PI_2 ;
}
}}