/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	          		|
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
#include "math/statistical_tools.hpp"

#include "thermal/model/two_dim/analytical_2009/heat2DAna.hpp"
#include "thermal/emission/emission.hpp"
#include "thermal/analysis/kernal.hpp"

#include "thermal/simulations/Numerical_PhaseOfEmission.h"
#include "thermal/model/one_dim/numerical_2011/Numerical_Setup.h"
#include "thermal/model/one_dim/numerical_2011/Numerical_Temperature.h"
#include "thermal/define/model.hpp"
#include "thermal/define/temperature.h"
#include "thermal/define/lthermal.h"


double PhaseOfEmission1DNum( const double omega,
                             const thermal::analysis::Kernal &popteaCore)
{
  using thermal::define::Temperature;
  Temperature Tprofile( popteaCore.thermalsys.mesh.Nend,
                        popteaCore.thermalsys.mesh.M2 ) ;

  //// Acquire Numerical Temperature
  temperature_1D( popteaCore.TBCsystem,
                  popteaCore.thermalsys,
                  popteaCore.expSetup, omega, Tprofile ) ;

  ///Initiate emission model
  const double Lcoat = popteaCore.TBCsystem.coating.depth ;
  const class thermal::Emission emission( popteaCore.expSetup.detector.wavelength,
                                          popteaCore.TBCsystem.Temp.base,
                                          popteaCore.thermalsys.mesh,
                                          popteaCore.bEval() * Lcoat,
                                          popteaCore.TBCsystem.optical.Emit1 ) ;

  const double phase2 = emission.phase1D( Tprofile ) ;
  Tprofile.cleanup();

  return phase2;
}

double PhaseOfEmission2DAna( const double omega,
                             const class thermal::analysis::Kernal &popteaCore)
{
    /// Initiate 2d analytical model
    const double k_coat  = popteaCore.TBCsystem.coating.kthermal.offset;
    const double psi_coat= popteaCore.TBCsystem.coating.psithermal.offset;
    const double Lcoat = popteaCore.TBCsystem.coating.depth;
    const double csub = popteaCore.TBCsystem.substrate.c;
    const double ccoat = popteaCore.TBCsystem.coating.c;

    const class HeatModel2DAna
        heatmodel2DAna( popteaCore.TBCsystem.optical.R0,
                        popteaCore.TBCsystem.optical.R1,
                        popteaCore.TBCsystem.coating.lambda,
                        popteaCore.expSetup.laser.It,
                        csub, popteaCore.TBCsystem.a_subEval(),
                        popteaCore.TBCsystem.gammaEval(),
                        popteaCore.bEval(), k_coat, Lcoat, psi_coat, ccoat,
                        popteaCore.TBCsystem.substrate.lambda,
                        popteaCore.thermalsys.mesh) ;

    /// Setup Temperature[n][r][z] Vector
    std::vector< std::vector< std::vector< double > > > T2DProfile;
    vector3DSetup(T2DProfile, popteaCore.thermalsys.mesh.Nend,
                  popteaCore.thermalsys.mesh.Rend,
                  popteaCore.thermalsys.mesh.M2);

    ///Populate Temperature Vector
    heatmodel2DAna.TemperatureDistro(T2DProfile, omega );

    ///Initiate emission model
    const thermal::Emission emission( popteaCore.expSetup.detector.wavelength,
                                      popteaCore.TBCsystem.Temp.referance,
                                      popteaCore.thermalsys.mesh,
                                      popteaCore.bEval() * Lcoat,
                                      popteaCore.TBCsystem.optical.Emit1
                                      );

    const double phase2d = emission.phase2D(T2DProfile);
    return phase2d;
}




double PhaseOfEmission1DAna( const double omega1, const double L_coat,
                             const double k_c, const double psi_c,
                             const double lambda, const double R1,
                             const double gamma, const double Esigma )
{
  using thermal::define::lthermal;
  const double l = lthermal( L_coat , k_c , psi_c , omega1 ) ;

  /*See 2004 emission paper equation 19*/
  constexpr std::complex<double> _i_ ( 0.0 , 1.0 ) ;
  const std::complex<double> SQRTi = std::sqrt(_i_);
  std::complex<double> M = 1;
  std::complex<double> N = 1;
  {
    const std::complex<double> sinhSQRTi = std::sinh( SQRTi / l ) ;
    const std::complex<double> coshSQRTi = std::cosh( SQRTi / l ) ;
    const std::complex<double> gammaXcoshSQRTplusSinhSQRT = gamma * coshSQRTi + sinhSQRTi;

    M -= SQRTi * lambda / l * sinhSQRTi / std::sinh( 1 / lambda ) ;
    M /= gammaXcoshSQRTplusSinhSQRT ;

    N -= _i_ * lambda * lambda / l / l * coshSQRTi / std::cosh( 1 / lambda ) ;
    N /= gammaXcoshSQRTplusSinhSQRT ;
  }

  const double exp2lambda = std::exp( -2 / lambda ) ;
  std::complex<double>
  A =  1 + R1 ;
  A *= 1 - exp2lambda;
  A *= M;

  std::complex<double>
  B =  1 - R1 ;
  B *= 1 + exp2lambda ;
  B *= N;

  const std::complex<double> t = A + B;
  const std::complex<double> u  = 2. * ( 1. - lambda * lambda / l / l * _i_ ) ;
  const std::complex<double> v = Esigma * SQRTi / l - 4 * gamma ;
  const double R1xExp2lambdaPLUS1 = std::fma( -R1, exp2lambda, 1 );

  return std::arg( v/u*t + 4 * R1xExp2lambdaPLUS1 ) - M_PI_2 ;
}

double PhaseOfEmission1DAna( const double omega1,
                             const thermal::analysis::Kernal &popteaCore )
{
  const double L_coat   = popteaCore.TBCsystem.coating.depth ;
  const double k_c      = popteaCore.TBCsystem.coating.kthermal.offset ;
  const double psi    = popteaCore.TBCsystem.coating.psithermal.offset ;
  const double lambda   = popteaCore.TBCsystem.coating.lambda ;
  const double R1       = popteaCore.TBCsystem.optical.R1 ;
  const double gamma    = popteaCore.TBCsystem.gammaEval() ;
  const double E1   = popteaCore.TBCsystem.optical.Emit1;
  
  const double output = PhaseOfEmission1DAna( omega1, L_coat, k_c, psi, lambda,
                                              R1, gamma, E1 ) ;
  
  return output ;
}

