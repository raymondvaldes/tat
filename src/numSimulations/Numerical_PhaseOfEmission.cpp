/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
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
#include "thermal/analysis/kernal.hpp"
#include "numSimulations/Numerical_Temperature.h"
#include "numSimulations/Numerical_PhaseOfEmission.h"
#include "algorithms/statistical_tools.hpp"
#include "numSimulations/Numerical_Setup.h"
#include "thermal/emission.hpp"
#include "thermal/model.hpp"

double PhaseOfEmission1DNum( const int flag,
                             const class thermal::analysis::Kernal &popteaCore)
{
  class Temperature Tprofile( popteaCore.thermalsys.mesh.Nend,
                              popteaCore.thermalsys.mesh.M2);

  //// Acquire Numerical Temperature
  const double omega = popteaCore.expSetup.laser.omegas[flag];
  temperature_1D( popteaCore.TBCsystem,
                  popteaCore.thermalsys,
                  popteaCore.expSetup, omega, Tprofile);

  ///Initiate emission model
  const double Lcoat = popteaCore.TBCsystem.coating.depth;
  const class thermal::Emission emission( popteaCore.expSetup.detector.wavelength,
                                          popteaCore.TBCsystem.Temp.base,
                                          popteaCore.thermalsys.mesh,
                                          popteaCore.bEval() *Lcoat,
                                          popteaCore.TBCsystem.optical.Emit1 );

  const double phase2 = emission.phase1D( Tprofile );
  Tprofile.cleanup();

  return phase2;
}

double PhaseOfEmission2DAna( const int flag,
                             const class thermal::analysis::Kernal &popteaCore )
{
    /// Initiate 2d analytical model
    const double k_coat  = popteaCore.TBCsystem.coating.kthermal.offset;
    const double psi_coat= popteaCore.TBCsystem.coating.psithermal.offset;
    const double Lcoat = popteaCore.TBCsystem.coating.depth;
    const double csub = popteaCore.TBCsystem.substrate.c;
    const double ccoat = popteaCore.TBCsystem.coating.c;

    const class HeatModel2DAna heatmodel2DAna(popteaCore.TBCsystem.optical.R0,
                                              popteaCore.TBCsystem.optical.R1,
                                              popteaCore.TBCsystem.coating.lambda,
                                              popteaCore.expSetup.laser.It,
                                              csub, popteaCore.TBCsystem.a_subEval(),
                                              popteaCore.TBCsystem.gammaEval(),
                                              popteaCore.bEval(),
                                              k_coat, Lcoat, psi_coat,
                                              ccoat,
                                              popteaCore.TBCsystem.substrate.lambda,
                                              popteaCore.thermalsys.mesh);

    /// Setup Temperature[n][r][z] Vector
    std::vector< std::vector< std::vector< double > > > T2DProfile;
    vector3DSetup(T2DProfile, popteaCore.thermalsys.mesh.Nend,
                  popteaCore.thermalsys.mesh.Rend,
                  popteaCore.thermalsys.mesh.M2);

    ///Populate Temperature Vector
    heatmodel2DAna.TemperatureDistro(T2DProfile,
                                     popteaCore.expSetup.laser.omegas[flag]);

    ///Initiate emission model
    const class thermal::Emission emission(popteaCore.expSetup.detector.wavelength,
                                  popteaCore.TBCsystem.Temp.referance,
                                  popteaCore.thermalsys.mesh,
                                  popteaCore.bEval() * Lcoat,
                                  popteaCore.TBCsystem.optical.Emit1
                                  );

    const double phase2d = emission.phase2D(T2DProfile);
    return phase2d;
}


double PhaseOfEmission1DAna(const int flag,
                            const thermal::analysis::Kernal &popteaCore)
{
  /*See 2004 emission paper equation 19*/
  const double omega1 = popteaCore.expSetup.laser.omegas[flag];
  const double lambda = popteaCore.TBCsystem.coating.lambda;
  const double Esigma = popteaCore.TBCsystem.optical.Emit1;
  const double gamma  = popteaCore.TBCsystem.gammaEval();
  const double R1     = popteaCore.TBCsystem.optical.R1;
  const double L_coat = popteaCore.TBCsystem.coating.depth;
  const double k_c    = popteaCore.TBCsystem.coating.kthermal.offset;
  const double psi_c  = popteaCore.TBCsystem.coating.psithermal.offset;
  const double l = lthermal(L_coat,k_c,psi_c,omega1);

  constexpr std::complex<double> _i_ (0.0, 1.0);

  std::complex<double>
  M = 1;
  M -= sqrt(_i_) * lambda / l * sinh( sqrt(_i_)/l ) / sinh( 1/lambda ) ;
  M /=  gamma * cosh( sqrt(_i_)/l ) + sinh( sqrt(_i_)/l ) ;

  std::complex<double>
  N = 1 ;
  N -= _i_ * lambda * lambda / l / l * cosh( sqrt(_i_)/l ) / cosh( 1/lambda ) ;
  N /= gamma * cosh( sqrt(_i_)/l ) + sinh( sqrt(_i_)/l ) ;

  std::complex<double>
  A =  1 + R1 ;
  A *= 1 - exp(-2/lambda);
  A *= M;

  std::complex<double>
  B =  1 - R1 ;
  B *= 1 + exp(-2/lambda) ;
  B *= N;

  const std::complex<double>
  v = Esigma * sqrt(_i_) / l - 4 * gamma ;

  std::complex<double>
  u  = 2;
  u *=  1. - lambda * lambda / l / l * _i_  ;

  const std::complex<double>
  t = A + B;

  double
  phase_emit_ana_C = std::arg( v/u*t + 4 * ( 1. - R1 * exp(-2/lambda) ) ) ;
  phase_emit_ana_C -= M_PI_2;

  return phase_emit_ana_C;
}



Temperature::Temperature(const size_t Nend_, const size_t M2_)
: Nend(Nend_), M2(M2_)
{
  temperature = new double[Nend_ * M2_];
}

double Temperature::eval(const size_t i, const size_t j) const
{
  return temperature[j + M2 * i];
}

void Temperature::assgn(const size_t i, const size_t j, const double value)
{
  temperature[j + M2 * i] = value;
}

void Temperature::cleanup(void)
{
  delete[]temperature;
}

