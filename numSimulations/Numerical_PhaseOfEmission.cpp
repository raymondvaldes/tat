
#include "../Header.h"
double PhaseOfEmission1DNum(const int flag,
                            const struct parameterStr *const pStruct)
{
    class Temperature Tprofile(pStruct->mesh->Nend,
                               pStruct->mesh->M2);

    /// Acquire Numerical Temperature
    temperature_1D(
                   pStruct->laser->Is,    pStruct->laser->It,
                   pStruct->lambda,       pStruct->opticalProp->R0,
                   pStruct->opticalProp->R1,
                   pStruct->L_coat,       pStruct->L_substrate,
                   pStruct->q_surface,
                   pStruct->TemperatureScale->tolerance,
                   pStruct->iter,
                   pStruct->TemperatureScale->rear,
                   pStruct->laser->omegas[flag],
                   pStruct->gamma,
                   pStruct->k1_thermal,   pStruct->k2_thermal,
                   pStruct->psi1_thermal, pStruct->psi2_thermal,
                   pStruct->mesh, Tprofile);

    ///Initiate emission model
    const class Emission*
    emission = new class Emission(pStruct->detector_lam,
                                  pStruct->TemperatureScale->base,
                                  pStruct->mesh,
                                  pStruct->bNorm *pStruct->L_coat,
                                  pStruct->E_sigma);
    const double
    phase2 = emission->phase1D(Tprofile);

    ///clean up
    Tprofile.cleanup();
    emission->cleanup();
    delete emission;

    return phase2;
}

double PhaseOfEmission2DAna(const int flag,
                            const struct parameterStr *const pStruct)
{
    /// Initiate 2d analytical model
    const double k_coat     = pStruct->k1_thermal->offset;
    const double psi_coat   = pStruct->psi1_thermal->offset;

    const class HeatModel2DAna heatmodel2DAna(pStruct->opticalProp->R0,
                                              pStruct->opticalProp->R1,
                                              pStruct->lambda,
                                              pStruct->laser->It,
                                              pStruct->c_sub, pStruct->a_sub,
                                              pStruct->gamma, pStruct->bNorm,
                                              k_coat, pStruct->L_coat, psi_coat,
                                              pStruct->c_coat,
                                              pStruct->lambda_Sub,
                                              pStruct->mesh);

    /// Setup Temperature[n][r][z] Vector
    std::vector< std::vector< std::vector< double > > > T2DProfile;
    vector3DSetup(T2DProfile, pStruct->mesh->Nend, pStruct->mesh->Rend,
                  pStruct->mesh->M2);

    ///Populate Temperature Vector
    heatmodel2DAna.TemperatureDistro(T2DProfile, pStruct->laser->omegas[flag]);
    heatmodel2DAna.cleanup();

    ///Initiate emission model
    const class Emission* emission;
    emission = new class Emission(pStruct->detector_lam,
                                 pStruct->TemperatureScale->referance,
                                  pStruct->mesh,
                                  pStruct->bNorm * pStruct->L_coat,
                                  pStruct->E_sigma);

    const double
    phase2d = emission->phase2D(T2DProfile);

    ///clean up
    emission->cleanup();
    delete emission;

    return phase2d;
}


double PhaseOfEmission1DAna(const int flag,
                            const struct parameterStr*const pStruct)
{
    /*See 2004 emission paper equation 19*/
    const double omega1 = pStruct->laser->omegas[flag];
    const double lambda = pStruct->lambda;
    const double Esigma  = pStruct->E_sigma;
    const double gamma  = pStruct->gamma;
    const double R1     = pStruct->opticalProp->R1;
    const double L_coat = pStruct->L_coat;
    const double k_c    = pStruct->k1_thermal->offset;
    const double psi_c  = pStruct->psi1_thermal->offset;
    const double l = lthermal(L_coat,k_c,psi_c,omega1);

//#define  _i std::complex<double>(0.,1.)
    constexpr std::complex<double> _i_ (0.0, 1.0);

    std::complex<double> M, N, A, B, v, u, t;
    M = 1;
    M -= sqrt(_i_) * lambda / l * sinh( sqrt(_i_)/l ) / sinh( 1/lambda ) ;
    M /=  gamma * cosh( sqrt(_i_)/l ) + sinh( sqrt(_i_)/l ) ;

    N = 1 ;
    N -= _i_ * lambda * lambda / l / l * cosh( sqrt(_i_)/l ) / cosh( 1/lambda ) ;
    N /= gamma * cosh( sqrt(_i_)/l ) + sinh( sqrt(_i_)/l ) ;

    A =  1 + R1 ;
    A *= 1 - exp(-2/lambda);
    A *= M;

    B =  1 - R1 ;
    B *= 1 + exp(-2/lambda) ;
    B *= N;

    v = Esigma * sqrt(_i_) / l - 4 * gamma ;

    u  = 2;
    u *=  1. - lambda * lambda / l / l * _i_  ;

    t = A + B;

    double
    phase_emit_ana_C = std::arg( v/u*t + 4 * ( 1. - R1 * exp(-2/lambda) ) ) ;
    phase_emit_ana_C -= M_PI_2;

    return phase_emit_ana_C;
}



Temperature::Temperature(const size_t Nend_, const size_t M2_)
: Nend(Nend_), M2(M2_)
{
    temperature = new double[Nend * M2]{0};
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
