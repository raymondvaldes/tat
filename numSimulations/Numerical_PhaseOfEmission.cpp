
#include "../Header.h"
double PhaseOfEmission1DNum(const int flag,
                            const class thermalAnalysisMethod::PopTea poptea)
{
  class Temperature Tprofile(poptea.thermalModel.mesh->Nend,
                             poptea.thermalModel.mesh->M2);

  //// Acquire Numerical Temperature
  temperature_1D(poptea.TBCsystem.coating.lambda,
                 poptea.TBCsystem.optical.R1,
                 poptea.expSetup.q_surface,
                 poptea.thermalModel.iter,
                 poptea.expSetup.laser.omegas[flag],
                 poptea.TBCsystem.gammaEval(),
                 poptea.thermalModel.mesh, Tprofile,
                 poptea.expSetup.laser,
                 poptea.TBCsystem
                 );

  ///Initiate emission model
  const double Lcoat = poptea.TBCsystem.coating.depth;
  const class Emission emission(poptea.expSetup.detector.wavelength,
                                poptea.TBCsystem.Temp.base,
                                poptea.thermalModel.mesh,
                                poptea.bEval() *Lcoat,
                                poptea.TBCsystem.optical.Emit1
                                );

  const double phase2 = emission.phase1D(Tprofile);
  Tprofile.cleanup();

  return phase2;
}

double PhaseOfEmission2DAna(const int flag,
                            const class thermalAnalysisMethod::PopTea poptea)
{
    /// Initiate 2d analytical model
    const double k_coat  = poptea.TBCsystem.coating.kthermal.offset;
    const double psi_coat= poptea.TBCsystem.coating.psithermal.offset;
    const double Lcoat = poptea.TBCsystem.coating.depth;
    const double csub = poptea.TBCsystem.substrate.c;
    const double ccoat = poptea.TBCsystem.coating.c;

    const class HeatModel2DAna heatmodel2DAna(poptea.TBCsystem.optical.R0,
                                              poptea.TBCsystem.optical.R1,
                                              poptea.TBCsystem.coating.lambda,
                                              poptea.expSetup.laser.It,
                                              csub, poptea.TBCsystem.a_subEval(),
                                              poptea.TBCsystem.gammaEval(),
                                              poptea.bEval(),
                                              k_coat, Lcoat, psi_coat,
                                              ccoat,
                                              poptea.TBCsystem.substrate.lambda,
                                              poptea.thermalModel.mesh);

    /// Setup Temperature[n][r][z] Vector
    std::vector< std::vector< std::vector< double > > > T2DProfile;
    vector3DSetup(T2DProfile, poptea.thermalModel.mesh->Nend,
                  poptea.thermalModel.mesh->Rend,
                  poptea.thermalModel.mesh->M2);

    ///Populate Temperature Vector
    heatmodel2DAna.TemperatureDistro(T2DProfile,
                                     poptea.expSetup.laser.omegas[flag]);

    ///Initiate emission model
    const class Emission emission(poptea.expSetup.detector.wavelength,
                                  poptea.TBCsystem.Temp.referance,
                                  poptea.thermalModel.mesh,
                                  poptea.bEval() * Lcoat,
                                  poptea.TBCsystem.optical.Emit1
                                  );

    const double phase2d = emission.phase2D(T2DProfile);
    return phase2d;
}


double PhaseOfEmission1DAna(const int flag,
                            const class thermalAnalysisMethod::PopTea poptea)
{
  /*See 2004 emission paper equation 19*/
  const double omega1 = poptea.expSetup.laser.omegas[flag];
  const double lambda = poptea.TBCsystem.coating.lambda;
  const double Esigma = poptea.TBCsystem.optical.Emit1;
  const double gamma  = poptea.TBCsystem.gammaEval();
  const double R1     = poptea.TBCsystem.optical.R1;
  const double L_coat = poptea.TBCsystem.coating.depth;
  const double k_c    = poptea.TBCsystem.coating.kthermal.offset;
  const double psi_c  = poptea.TBCsystem.coating.psithermal.offset;
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
//  temperature.resize(Nend * M2);
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

emissionNoiseParameters::emissionNoiseParameters(const double a1_,
                                                 const double b1_,
                                                 const bool d1_, const bool d2_,
                                                 const int s1_,
                                                 const double noiseRandom_):
    a(a1_), b(b1_), noiseRandom(noiseRandom_), d1(d1_), d2(d2_), s1(s1_)
{}
