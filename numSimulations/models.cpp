#include "../Header.h"
ThermalModel::ThermalModel(const enum HeatX myHeat,
                           const enum EmissionX myEmission)
:heat(myHeat), emission(myEmission){}



HeatModel2DAna::HeatModel2DAna(const double R0_, const double R1_,
                               const double lambda_, const double It_,
                               const double csub_, const double asub_,
                               const double gamma_, const double beam_,
                               const double k_coat_, const double L_,
                               const double psi_coat_, const double ccoat_,
                               const double lambda_Sub_,
                               const class Mesh *mesh_):
                               R0(R0_), R1(R1_), lambda(lambda_), It(It_),
                               csub(csub_), asub(asub_), gamma(gamma_),
                               beam(beam_), k_coat(k_coat_), L(L_),
                               psi_coat(psi_coat_), ccoat(ccoat_),
                               lambda_Sub(lambda_Sub_), mesh(mesh_)
{
    if(R0_ < 0 || R0_ > 1 || R1_ < 0 || R1_ > 1 || lambda_ < 0)
    {
        std::cout << "\ninput errors in radJ2" << R0_ <<"\t" << R1_ << "\t";
        std::cout << lambda_<< "\n";
        exit(-99);
    }

    funcComplex = new std::complex<double>[nuSize];
    funcComplexR = new std::complex<double>[nuSize * mesh->Rend];
    funcComplexZ = new std::complex<double>[nuSize * mesh->M2];
    nuSpace = new double[nuSize];

    funcReal = new double[nuSize];
    funcImag = new double[nuSize];

    ::range(nuSpace, nuStart, nuEnd, nuSize);
}

void HeatModel2DAna::cleanup(void) const
{
    delete[] funcComplex;
    delete[] funcComplexR;
    delete[] funcComplexZ;
    delete[] nuSpace;

    delete[] funcReal;
    delete[] funcImag;
}

double HeatModel2DAna::radJ0(void) const
{
    /*
    Radiosity J0 is the flux into the coating from the top surface
    */

//    std::cout << R0 <<"\t"<<R1<<"\t" << "\t" << lambda;
//    exit(-24);
    const double
    product =  R0 * R1 * exp(-2./lambda);

    return 1 + product / (1.- product);
}

double HeatModel2DAna::radJ1(void) const
{
    /*
    Radiosity J1 is the flux into the coating from the interface
    */

    double
    radiosity  = R1 * exp(-1./lambda);
    radiosity /= 1 - R0 * R1 * exp(-2./lambda);

    return radiosity;
}

double HeatModel2DAna::radJ2(void) const
{
    /*
    Radiosity J2 is the flux into the substrate from the interface
    */
    double
    radiosity  = 1;
    radiosity -= R1;

    radiosity *= exp(-1./lambda);
    radiosity /= 1 - R0 * R1 * exp(-2./lambda);

    return radiosity;
}

double HeatModel2DAna::gSpatial(const double zNorm) const
{
    /*
    zNorm is the axial spatial parameter of the volumetric heating
    distribution.  Care must be taken to ensure that zNorm is normalized
    for the coating thickness
    */

    const double J0 = radJ0();
    const double J1 = radJ1();
    const double J2 = radJ2();

    const double z = zNorm;
    if(z <= 1)
    {
        return J0 * exp( -z * lambda ) + J1 * exp( ( z - 1 ) * lambda);
    }
    else if (z > 1)
    {
        return J2 * exp( ( 1 - z ) * lambda_Sub ) ;
    }
    else if(z < 0)
    {
        std::cout << "error in gspatial!\n\n";
        exit(-55);
    }
    return 0;
}

std::complex<double> HeatModel2DAna::nuTilde(const double nu,
                                             const double ltherm) const
{
    double
    realNum = nu;
    realNum *= ccoat;
    realNum *= ltherm;
    realNum /= beam;
    realNum *= realNum;
    const std::complex<double> resultant (realNum, 1);

    return sqrt(resultant);
}

std::complex<double> HeatModel2DAna::nuHat(const double nu,
                                           const double ltherm) const
{
    double
    realNum = nu;
    realNum *= asub;
    realNum *= ltherm;
    realNum /= beam;
    realNum *= realNum;
    const std::complex<double> resultant (realNum, 1);

    return sqrt(resultant);
}

std::complex<double> HeatModel2DAna::fFunc(const double nu,
                                           const double ltherm ) const
{
    const std::complex<double> nuHAT = nuHat(nu, ltherm);
    const std::complex<double> nuTIlde = nuTilde(nu, ltherm);

    return fFunc(nu, ltherm,nuHAT,nuTIlde );
}

std::complex<double> HeatModel2DAna::fFunc(const double nu, const double ltherm,
                                           const std::complex<double> nuHAT,
                                           const std::complex<double> nuTIlde)
                                           const
{
    std::complex<double>
    retrn = tanh( nuTIlde / ltherm);
    retrn *= gamma;
    retrn *= nuHAT;
    retrn += nuTIlde;

    std::complex<double>
    retrn1 = tanh( nuTIlde / ltherm) ;
    retrn1 *= nuTIlde;
    retrn1 += nuHAT * gamma;

    return retrn / retrn1;
}

std::complex<double> HeatModel2DAna::HFunc(const double nu, const double ltherm,
                                           const double z) const
{
    const std::complex<double> nuHAT = nuHat(nu, ltherm);
    const std::complex<double> nuTIlde = nuTilde(nu, ltherm);
    return HFunc(nu, ltherm, z, nuHAT ,nuTIlde );
}

std::complex<double>
HeatModel2DAna::HFunc(const double nu, const double ltherm, const double zNorm,
                      const std::complex<double> nuHAT,
                      const std::complex<double> nuTIlde) const
{
    const double z = zNorm;

    std::complex<double>
    retrn = nuHAT;
    retrn *= lambda;
    retrn *= gamma;
    retrn /= ltherm;
    retrn += 1;
    retrn *= 1 + R1;
    retrn *= -1;
    retrn += 2;

    std::complex<double>
    retrn5 = nuTIlde;
    retrn5 *= lambda;
    retrn5 /= ltherm;
    retrn5 *= retrn5;
    retrn5 -= 1;
    retrn5 *= 1 - R1;

    std::complex<double>
    retrn1a  = sinh(nuTIlde / ltherm);
    retrn1a *= nuTIlde;

    std::complex<double>
    retrn1b = cosh(  nuTIlde * z / ltherm );
    retrn1b *= nuTIlde ;

    std::complex<double>
    retrn1 = cosh( nuTIlde / ltherm );
    retrn1 *= nuHAT ;
    retrn1 *= gamma ;
    retrn1 += retrn1a;
    retrn1 = 1./retrn1;
    retrn1 *= retrn1b;

    std::complex<double>
    retrn2a =  nuTIlde;
    retrn2a *= z;
    retrn2a /= ltherm ;

    std::complex<double>
    retrn2b = fFunc(nu, ltherm, nuHAT, nuTIlde);
    retrn2b *= cosh(retrn2a);

    std::complex<double>
    retrn2 = sinh( retrn2a );
    retrn2 -= retrn2b ;
    retrn2 *= exp(-1/lambda) ;
    retrn2 *= R1;
    retrn2 *= (1 - R0);

    double
    retrn3a  = R0;
    retrn3a *= exp( (-z - 1 ) / lambda);
    retrn3a += exp( ( z - 1 ) / lambda);
    retrn3a *= R1 ;

    std::complex<double>
    retrn3 = nuTIlde;
    retrn3 *= lambda;
    retrn3 /= ltherm;
    retrn3 *= retrn3a;

    std::complex<double>
    retrn6 = retrn;
    retrn6 += retrn5;
    retrn6 *= retrn1;
    retrn6 += retrn3 - retrn2;
    return retrn6;
}

std::complex<double>
HeatModel2DAna::hTildeCoat(const double nu, const double ltherm,
                           const double zNorm) const
{
    const double retrn1a = ltherm * exp(-nu*nu / 4);
    const std::complex<double> nuHAT = nuHat(nu, ltherm);
    const std::complex<double> nuTIlde = nuTilde(nu, ltherm);

    std::complex<double>
    retrn1b = nuTIlde;
    retrn1b *= lambda;
    retrn1b /= ltherm;
    retrn1b *= retrn1b;

    std::complex<double>
    retrn1 = retrn1b;
    retrn1 -= 1.;
    retrn1 *= 2.;
    retrn1 *= nuTIlde;
    retrn1 = 1. / retrn1;
    retrn1 *= retrn1a;

    std::complex<double>
    retrn2 = nuTIlde;
    retrn2 *= lambda;
    retrn2 /= ltherm;
    retrn2 *= exp(-zNorm/lambda);

    std::complex<double>
    retrn3 = HFunc(nu, ltherm, zNorm, nuHAT, nuTIlde);
    retrn3 *= exp( -1 / lambda );
    retrn3 /=  1 - R0 * R1 * exp( -2 / lambda );

    std::complex<double>
    retrn4a  =  nuTIlde;
    retrn4a *= zNorm;
    retrn4a /= ltherm;

    std::complex<double>
    retrn4b  = fFunc(nu, ltherm, nuHAT, nuTIlde);
    retrn4b *= cosh(retrn4a);

    std::complex<double>
    retrn4 = sinh( retrn4a );
    retrn4 -= retrn4b;

    std::complex<double>
    retrn5 = retrn2;
    retrn5 += retrn3;
    retrn5 += retrn4;
    retrn5 *= retrn1;

    return retrn5 ;
}

std::complex<double>
HeatModel2DAna::hTildeSubstrate(const double nu, const double ltherm,
                                const double zNorm) const
{
    if(zNorm <= 1)
    {
        std::cout << "\nerror in 2d Analytical temperature\n";
        exit(-97);
    }

    const double z = zNorm;
    const std::complex<double> nuHAT = nuHat(nu, ltherm);

    std::complex<double>
    retrn = nuHAT * (z-1.);
    retrn /= (asub * ltherm);
    retrn *= -1;
    retrn = exp(retrn);

    return retrn *  hTildeCoat(nu, ltherm, 1.);
}

std::complex<double>
HeatModel2DAna::iHankel(std::complex<double>(HeatModel2DAna::*hfunc)
                        (const double, const double, const double) const,
                        const double r, const double z, const double ltherm)
                        const
{
    /*
    The definite integral of a complex integrand is the sum if the
    intregral of real and complex parts.

    Int[f(x),a,b] = Int[u(x)+i*v[x],a,b] = Int[u(x),a,b] + i * Int[v[x],a,b]
    */

    for(size_t i = 0; i < nuSize ;  ++i)
    {
        const double nu = nuSpace[i];
        funcComplex[i] = (this->*hfunc)(nu, ltherm, z);
        funcComplex[i] *= gsl_sf_bessel_J0( nu * r ) * nu;

        funcReal[i] = funcComplex[i].real();
        funcImag[i] = funcComplex[i].imag();
    }

    ///Integrate each one independently
    const size_t xlow =  0;
    const size_t xhigh = nuSize-1;

    const double
    sumReal = ::simpson_3_8(funcReal, nuSpace, xlow, xhigh);

    const double
    sumImag = ::simpson_3_8(funcImag, nuSpace, xlow, xhigh);

    ///Cleanup
    const std::complex<double> sum (sumReal, sumImag);
    return sum;
}

std::complex<double>
HeatModel2DAna::theta(const double r, const double z, const double ltherm) const
{
    ///execute inverse hankel
    std::complex<double> iHankelResult;
    if(z <= 1 && z >= 0)
    {
        iHankelResult = iHankel(&HeatModel2DAna::hTildeCoat, r, z, ltherm);
    }
    else if (z > 1)
    {
        iHankelResult = iHankel(&HeatModel2DAna::hTildeSubstrate, r, z, ltherm);
    }

    return iHankelResult;
}

std::complex<double>
HeatModel2DAna::TempTComplex(const double r, const double z,
                             const double ltherm) const
{
    return theta(r, z, ltherm) * ( L * It * ( 1 - R0 ) / k_coat );
}

double
HeatModel2DAna::TempT(const double r, const double z, const double tau_,
                      const double omega) const
{
    /*
    The transient temperature (real). The parameters are normalized
    including time.
    */
    const double ltherm = ::lthermal(L, k_coat, psi_coat, omega);
    constexpr std::complex<double> _i_ (0.0, 1.0);

    std::complex<double>
    TempComplex = TempTComplex(r, z, ltherm);
    TempComplex *= exp(_i_ * 2. * M_PI * tau_);

    return real(TempComplex);
}

std::complex<double>
HeatModel2DAna::iHankel(const size_t r, const size_t z) const
{
    for(size_t n = 0; n < nuSize ;  ++n)
    {
        funcComplex[n]  = funcComplexZ[z + n*mesh->M2];
        funcComplex[n] *= funcComplexR[r + n*mesh->Rend];

        funcReal[n] = funcComplex[n].real();
        funcImag[n] = funcComplex[n].imag();
    }

    ///Integrate each one independently
    const size_t xlow =  0;
    const size_t xhigh = nuSize - 1;


    return simpson_3_8Complex(funcReal, funcImag ,nuSpace,xlow,xhigh);
}

void
HeatModel2DAna::TemperatureDistro(std::vector<std::vector<std::vector<double>>>
                                  &Temperature, const double omega) const
{
    ///Determine the thermal penetration based on the omega
    const double ltherm = ::lthermal(L, k_coat, psi_coat, omega);
    constexpr   std::complex<double> _i_ (0.0, 1.0);

    ///Populate working arrays
    CPLXWorkingArrays(ltherm);

    ///Implement with working arrays
    for(size_t r = 0; r < mesh->Rend; ++r)
    {
        for(size_t z = 0; z < mesh->M2; ++z)
        {
            const std::complex<double> TempTComplexSol =
            iHankel(r, z) * ( L * It * ( 1 - R0 ) / k_coat );

            for(size_t n = 0; n < mesh->Nend; ++n)
            {
                const std::complex<double> TempTComplexI =
                TempTComplexSol * exp( _i_ * 2. * M_PI * mesh->tau[n] );

                Temperature[n][r][z]  = real(TempTComplexI);
            }
        }
    }

}

void
HeatModel2DAna::TemperaturePrintOut(const double omega,
                                    const std::string dir, const double L_coat)
                                    const
{
    /// Setup Temperature[n][r][z] Vector
    std::vector< std::vector< std::vector< double > > > T2DProfile;
    vector3DSetup(T2DProfile, mesh->Nend, mesh->Rend, mesh->M2);

    for(size_t n = 0; n < mesh->Nend; ++n)
    {
        std::ofstream myfile;
        std::stringstream filename;
        filename << dir  << "/" <<"../data/T2DProfile/T" << n <<".dat";
        myfile.open(filename.str().c_str());
        myfile << std::setprecision(8);

        for(size_t i = 0; i < mesh->Rend; ++i)
        {
            for(size_t j = 0; j < mesh->M2; ++j)
            {
                if(j <= mesh->M1)
                {
                    myfile << mesh->zNorm2[j] << "\t" ;
                    myfile << mesh->rReal[i] / L_coat << "\t";
                    myfile << T2DProfile[n][i][j] << "\n";
                }
                else if(j > mesh->M1)
                {
                    myfile << mesh->zNorm2[j] << "\t" ;
                    myfile << mesh->rReal[i] / L_coat << "\t";
                    myfile << T2DProfile[n][i][j] << "\n";
                }
            }
        }
        myfile.close();
    }
}

void
HeatModel2DAna::CPLXWorkingArrays(const double ltherm) const
{
    ///workspaces
    for(size_t n = 0 ; n < nuSize; ++n)
    {
        const double nu = nuSpace[n];
        for(size_t z = 0; z < mesh->M2; ++z)
        {

            if(z <= mesh->M1)
            {
                funcComplexZ[z + n*mesh->M2] = hTildeCoat(nu, ltherm,
                                                          mesh->zNorm2[z]);

            }
            else if(z > mesh->M1 && z < mesh->M2)
            {
                funcComplexZ[z + n*mesh->M2] = hTildeSubstrate(nu, ltherm,
                                                               mesh->zNorm2[z]);
            }
        }

        for(size_t r = 0; r < mesh->Rend; ++r)
        {
            funcComplexR[r + n*mesh->Rend] =
            gsl_sf_bessel_J0( nu * mesh->rNorm[r] ) * nu;
        }
    }
}



void HeatModel2DAna::testing(void) const
{
    constexpr size_t precO = 14;
    constexpr double nuInc = 0.25;
    constexpr double _nuEnd = 2;
    constexpr double ltherm = 1;

    std::cout<< "Input Parameters\n*************************************";
    std::cout << "*************************\n";
    std::cout << std::scientific << std::setprecision(precO);
    std::cout << "R0 = \t\t"        << R0 << "\nR1 = \t\t" << R1 << "\n";
    std::cout << "lambda = \t"      << lambda       << "\n";
    std::cout << "lambda_Sub = \t"  << lambda_Sub   << "\n";
    std::cout << "beam = \t\t"  << beam     << "\n";
    std::cout << "ccoat = \t"   << ccoat    << "\n";
    std::cout << "asub = \t\t"  << asub     << "\n";
    std::cout << "gamma = \t" << gamma    << "\n";
    std::cout << "It = \t\t"  << It     << "\n";
    std::cout << "k_coat = \t" <<k_coat    << "\n";
    std::cout << "ltherm = \t" <<ltherm    << "\n";

    std::cout << "*******************************************************";
    std::cout << "*******\n";

    std::cout << "\nOutput\n*************************************";
    std::cout << "*************************\n";
    std::cout << "J0 = \t\t" << radJ0() << "\nJ1 = \t\t" << radJ1() << "\n";
    std::cout << "J2 = \t\t" << radJ2() << "\n";
    std::cout << "\nzNormalized\tgSpatial(z)\n";
    for(size_t i = 0; i <= 8 ;  i++)
    {
        const double z = nuInc*i;
        std::cout << std::setprecision(2) << z <<"\t";
        std::cout << std::setprecision(precO) << gSpatial(z) << "\n";
    }


    for(size_t j = 0 ; j < 1; j++)
    {
        std::cout << std::setprecision(2) <<"\nfor: \n";
        std::cout << "lthermal = " << ltherm <<"\n";
        std::cout << "\n********\n";
        std::cout << "nu\t\tnuTilde(nu, lthermal)\n" ;
        for(size_t i = 0; i <= (_nuEnd/nuInc) ;  i++)
        {
            const double nu = nuInc*i;
            std::cout << std::setprecision(2) << nu << "\t";
            std::cout << std::setprecision(precO) << nuTilde(nu, ltherm) <<"\n";
        }
        std::cout << "\n********\n";

        std::cout << "\nnu\t\tnuHat(nu, lthermal)\n" ;
        for(size_t i = 0; i <= (_nuEnd/nuInc) ;  i++)
        {
            const double nu = nuInc*i;
            std::cout << std::setprecision(2) << nu << "\t";
            std::cout << std::setprecision(precO) << nuHat(nu, ltherm)<<"\n";
        }
        std::cout << "\n********\n";

        std::cout << "\nnu\t\tfFunc(nu, lthermal)\n" ;
        for(size_t i = 0; i <= (_nuEnd/nuInc) ;  i++)
        {
            const double nu = nuInc*i;
            std::cout << std::setprecision(2) << nu << "\t";
            std::cout << std::setprecision(precO) << fFunc(nu, ltherm) << "\n";
        }
        std::cout << "\n********\n";

        for(size_t i = 0 ; i < 3 ; ++i)
        {
            const double z = i;
            std::cout << std::setprecision(2);
            std::cout << "\nnu\t\tHFunc(nu, lthermal = " << ltherm;
            std::cout << ", z = " << z <<")\n" ;
            for(size_t k = 0; k <= (_nuEnd/nuInc) ;  k++)
            {
                const double nu = nuInc*k;
                std::cout << std::setprecision(2) << nu << "\t";
                std::cout << std::setprecision(precO) ;
                std::cout << HFunc(nu, ltherm, z)<<"\n";
            }
        }
        std::cout << "\n********\n";

        for(size_t i = 0 ; i <= 3 ; ++i)
        {
            const double z = i/3.;
            std::cout << std::setprecision(2);
            std::cout << "\nnu\t\thTildeCoat(nu, lthermal = " << ltherm;
            std::cout << ", z = " << z <<")\n" ;
            for(size_t k = 0; k <= (_nuEnd/nuInc) ;  k++)
            {
                const double nu = nuInc * k;
                std::cout << std::setprecision(2) << nu << "\t";
                std::cout << std::setprecision(precO) ;
                std::cout << hTildeCoat(nu, ltherm, z)<<"\n";
            }
        }
        std::cout << "\n********\n";

        for(size_t i = 0 ; i < 3 ; ++i)
        {
            const double z = 1.+(i+1.)/3.;
            std::cout << std::setprecision(2);
            std::cout << "\nnu\t\thTildeSubstrate(nu, lthermal = "<< ltherm;
            std::cout << ", z = " << z <<")\n" ;
            for(size_t k = 0; k <= (_nuEnd/nuInc) ;  k++)
            {
                const double nu = nuInc*k;
                std::cout << std::setprecision(2) << nu << "\t";
                std::cout << std::setprecision(precO) ;
                std::cout << hTildeSubstrate(nu, ltherm, z)<<"\n";
            }
        }
        std::cout << "\n********\n";

        for(size_t i = 0 ; i <= 3 ; ++i)
        {
            const double r = i*0.5;
            std::cout << std::setprecision(2);
            std::cout << "\nz\t\ttheta(nu, lthermal = "<< ltherm;
            std::cout << ", r = " << r <<")\n" ;
            for(size_t k = 0; k <= (_nuEnd/nuInc) ;  k++)
            {
                const double z = 0.5*k;
                std::cout << std::setprecision(2) << z << "\t";
                std::cout << std::setprecision(precO) ;
                std::cout << theta(r, z, ltherm)<<"\n";
            }
        }
        std::cout << "\n********\n";

        for(size_t i = 0 ; i <= 3 ; ++i)
        {
            const double r = i*0.5;
            std::cout << std::setprecision(2);
            std::cout << "\nz\t\tTempTComplex(nu, lthermal = "<< ltherm;
            std::cout << ", r = " << r <<")\n" ;
            for(size_t k = 0; k <= (_nuEnd/nuInc) ;  k++)
            {
                const double z = 0.5*k;
                std::cout << std::setprecision(2) << z << "\t";
                std::cout << std::setprecision(precO) ;
                std::cout << TempTComplex(r, z, ltherm)<<"\n";
            }
        }
        std::cout << "\n********\n";
        std::cout << "\n********\n";
    }



    std::cout << "*************************************";
    std::cout << "*************************\n";
}


Emission::Emission(const double detector_lam_, const double T_ref_,
                   const class Mesh *mesh_, const double beamR_,
                   const double E_sigma_):
                   detector_lam(detector_lam_), T_ref(T_ref_), mesh(mesh_),
                   beamR(beamR_), E_sigma(E_sigma_)
{
    Ib = new double[mesh->M1+1];
    EmissionTime = new double[mesh->Nend];
}

double Emission::mean(const double x1, const double x2) const
{
    return (x1+x2) / 2;
}

double Emission::drArea(const double r0_, const double r1_) const
{
    /*Differential area of a radial axi-symmetric element
    The area returned is the actual area calculated from the normalized
    radial dimension and the thickness of the coating.*/
    const double r0 = r0_ * beamR;
    const double r1 = r1_ * beamR;

    return M_PI * ( r1 * r1 - r0 * r0 );
}

double Emission::Ib_plank(const double Temperature) const
{
    //Planck's law is used to describe the Planck distribution
    /*
    D1 Const in Planck's spectral energy    [W m^2 / sr]
    D2 Const in Planck's spectral energy    [m K]
    sigma   STefan Boltzmann constant   [W/(m^2 K^4)]

    See: Linear radiation model for phase of thermal emission spectrosopy
    Bennett and Yu, 2005
    Equation (6)
    */

    constexpr double C1     = .59552197e-16;
    constexpr double C2     = .01438769;
    constexpr double sigma  = 5.67051e-8;

    const double
    T = Temperature + T_ref;

    double
    Ibp = C1;
//    Ibp *= 2;
    Ibp /= pow( detector_lam , 5 ) ;
    Ibp /= exp( C2 / ( detector_lam * T ) ) - 1 ;
    Ibp /= sigma * pow( T_ref, 4 ) ; /*normalize*/

    return Ibp;
}

double Emission::emissionAxial(std::vector<double> &Temperature) const
{
    /*
    Calculates the volumetric emission flux with respect to the axial
    direction. The Temperature variable is a pointer to the axial
    temperature.
    */
    for(size_t j = 0 ; j <= mesh->M1 ; ++j)
    {
        Ib[j] = Ib_plank(Temperature[j]);
    }

    constexpr   size_t z0 = 0;
    const       size_t z1 = mesh->M1;

    return E_sigma * Ib[z1] + 4 * ::simpson_3_8(Ib, mesh->z_norm, z0, z1);
}

double Emission::emissionAxial(const class Temperature Tprofile,
                               const size_t nVal) const
{
    /*
    Calculates the volumetric emission flux with respect to the axial
    direction. The Temperature variable is a pointer to the axial
    temperature.
    */
    for(size_t j = 0 ; j <= mesh->M1 ; ++j)
    {
        Ib[j] = Ib_plank(Tprofile.eval(nVal,j));
    }

    constexpr   size_t z0 = 0;
    const       size_t z1 = mesh->M1;

    return E_sigma * Ib[z1] + 4 * ::simpson_3_8(Ib, mesh->z_norm, z0, z1);
}

double Emission::emissionAxialLinear(std::vector<double> &Temperature) const
{
    /*
    Calculates the volumetric emission flux with respect to the axial
    direction. The Temperature variable is a pointer to the axial
    temperature.
    */
    for(size_t j = 0 ; j <= mesh->M1 ; ++j)
    {
        Ib[j] = Temperature[j];
    }
    const size_t z0 = 0;
    const size_t z1 = mesh->M1;

    return E_sigma * Ib[z1] + 4 * ::simpson_3_8(Ib, mesh->z_norm, z0, z1);
}


double Emission::emissionVolumetric2D(std::vector<std::vector<double>>&
                                      Temperature) const
{
    /*
    Calculates the volumetric emission flux with respect to the axial
    direction. Assume Temperature is of the form Tempearture[r][z].
    */
    double emission = 0;

    {
        constexpr   size_t  r = 0;
        constexpr   double  r0 = 0;
        const       double  r1 = mean(mesh->rNorm[r], mesh->rNorm[r+1]);
        emission += emissionAxial(Temperature[r]) * drArea(r0,r1);
    }

    for(size_t r = 1 ; r < mesh->Rend - 1 ; r++)
    {
        const double r0 = mean(mesh->rNorm[r], mesh->rNorm[r-1]);
        const double r1 = mean(mesh->rNorm[r], mesh->rNorm[r+1]);
        emission += emissionAxial(Temperature[r]) * drArea(r0,r1);
    }

    {
        const size_t r = mesh->Rend - 1;
        const double r0 = mean(mesh->rNorm[r], mesh->rNorm[r-1]);
        const double r1 = mesh->rNorm[r];
        emission += emissionAxial(Temperature[r]) * drArea(r0,r1);
    }
    return emission;
}

double Emission::phase2D(std::vector< std::vector<std::vector<double>>>
                                 &Temperature) const
{
    /*
    The volumetric emission is determined for one unique period of heating
    and then a cosine function is fitted.  The resulting phase is reported.
    */
    double OAPemission[3] = {1, 1, -M_PI_2};

    for (size_t n = 0 ; n < mesh->Nend ; ++n )
    {
        EmissionTime[n] = emissionVolumetric2D( Temperature[n] );
    }

    ::cosfit(EmissionTime, mesh->tau, OAPemission, mesh->Nend);

    return OAPemission[2];
}

double Emission::phase1D(std::vector< std::vector< double > > &
                                 Temperature) const
{
    /*
    The volumetric emission is determined for one unique period of heating
    and then a cosine function is fitted.  The resulting phase is reported.
    */
    for (size_t n = 0 ; n < mesh->Nend ; ++n )
    {
        EmissionTime[n] = emissionAxial(Temperature[n]);
    }

    const double
    offsetInitial = ::average(::arrayMax(EmissionTime, mesh->Nend),
                              ::arrayMin(EmissionTime, mesh->Nend));
    const double
    amplitudeInitial = (::arrayMax(EmissionTime, mesh->Nend)
                        -::arrayMin(EmissionTime, mesh->Nend)) / 2;

    constexpr double
    phaseInitial = -M_PI_2;

    double OAPemission[3] = {offsetInitial, amplitudeInitial, phaseInitial};

    ::cosfit(EmissionTime, mesh->tau, OAPemission, mesh->Nend);

    return OAPemission[2];
}

double Emission::phase1D(const class Temperature Tprofile) const
{
    /*
    The volumetric emission is determined for one unique period of heating
    and then a cosine function is fitted.  The resulting phase is reported.
    */
    for (size_t n = 0 ; n < mesh->Nend ; ++n )
    {
        EmissionTime[n] = emissionAxial(Tprofile, n);
    }

    const double
    offsetInitial = ::average(::arrayMax(EmissionTime, mesh->Nend),
                              ::arrayMin(EmissionTime, mesh->Nend));
    const double
    amplitudeInitial = (::arrayMax(EmissionTime, mesh->Nend)
                        -::arrayMin(EmissionTime, mesh->Nend)) / 2;

    constexpr double
    phaseInitial = -M_PI_2;

    double OAPemission[3] = {offsetInitial, amplitudeInitial, phaseInitial};

    ::cosfit(EmissionTime, mesh->tau, OAPemission, mesh->Nend);

//    exit(-1);

    return OAPemission[2];
}

void Emission::cleanup(void) const
{
    delete[] Ib;
    delete[] EmissionTime;
}
