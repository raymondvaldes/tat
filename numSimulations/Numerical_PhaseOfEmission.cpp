
#include "../Header.h"
double PhaseOfEmission1DNum(const int flag,
                            const struct parameterStr *const pStruct)
{
  class Temperature Tprofile(pStruct->mesh->Nend,
                             pStruct->mesh->M2);

  /// Acquire Numerical Temperature
  temperature_1D(pStruct->poptea->TBCsystem.coating.lambda,
                 pStruct->poptea->TBCsystem.optical.R1,
                 pStruct->q_surface,
                 pStruct->iter,
                 pStruct->laser->omegas[flag],
                 pStruct->poptea->TBCsystem.gammaEval(),
                 pStruct->mesh, Tprofile,
                 pStruct->poptea->expSetup.laser,
                 pStruct->poptea->TBCsystem
                 );

  ///Initiate emission model
  const double Lcoat = pStruct->poptea->TBCsystem.coating.depth;
  const class Emission emission(pStruct->poptea->expSetup.detector.wavelength,
                                pStruct->poptea->TBCsystem.Temp.base,
                                pStruct->mesh,
                                pStruct->poptea->bEval() *Lcoat,
                                pStruct->poptea->TBCsystem.optical.Emit1
                                );
  const double
  phase2 = emission.phase1D(Tprofile);

  ///clean up
  Tprofile.cleanup();
  return phase2;
}

double PhaseOfEmission2DAna(const int flag,
                            const struct parameterStr *const pStruct)
{
    /// Initiate 2d analytical model
    const double k_coat  = pStruct->poptea->TBCsystem.coating.kthermal.offset;
    const double psi_coat= pStruct->poptea->TBCsystem.coating.psithermal.offset;
    const double Lcoat = pStruct->poptea->TBCsystem.coating.depth;
    const double csub = pStruct->poptea->TBCsystem.substrate.c;
    const double ccoat = pStruct->poptea->TBCsystem.coating.c;

    const class HeatModel2DAna heatmodel2DAna(pStruct->poptea->TBCsystem.optical.R0,
                                              pStruct->poptea->TBCsystem.optical.R1,
                                              pStruct->poptea->TBCsystem.coating.lambda,
                                              pStruct->laser->It,
                                              csub, pStruct->poptea->TBCsystem.a_subEval(),
                                              pStruct->poptea->TBCsystem.gammaEval(),
                                              pStruct->poptea->bEval(),
                                              k_coat, Lcoat, psi_coat,
                                              ccoat,
                                              pStruct->poptea->TBCsystem.substrate.lambda,
                                              pStruct->mesh);

    /// Setup Temperature[n][r][z] Vector
    std::vector< std::vector< std::vector< double > > > T2DProfile;
    vector3DSetup(T2DProfile, pStruct->mesh->Nend, pStruct->mesh->Rend,
                  pStruct->mesh->M2);

    ///Populate Temperature Vector
    heatmodel2DAna.TemperatureDistro(T2DProfile, pStruct->laser->omegas[flag]);
    heatmodel2DAna.cleanup();

    ///Initiate emission model
    const class Emission emission(pStruct->poptea->expSetup.detector.wavelength,
                                  pStruct->poptea->TBCsystem.Temp.referance,
                                  pStruct->mesh,
                                  pStruct->poptea->bEval() * Lcoat,
                                  pStruct->poptea->TBCsystem.optical.Emit1
                                  );
    const double phase2d = emission.phase2D(T2DProfile);

    return phase2d;
}


double PhaseOfEmission1DAna(const int flag,
                            const struct parameterStr*const pStruct)
{
  /*See 2004 emission paper equation 19*/
  const double omega1 = pStruct->laser->omegas[flag];
  const double lambda = pStruct->poptea->TBCsystem.coating.lambda;
  const double Esigma = pStruct->poptea->TBCsystem.optical.Emit1;
  const double gamma  = pStruct->poptea->TBCsystem.gammaEval();
  const double R1     = pStruct->poptea->TBCsystem.optical.R1;
  const double L_coat = pStruct->poptea->TBCsystem.coating.depth;
  const double k_c    = pStruct->poptea->TBCsystem.coating.kthermal.offset;
  const double psi_c  = pStruct->poptea->TBCsystem.coating.psithermal.offset;
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

//Temperature::~Temperature()
//{
//  delete[]temperature;
//}

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
