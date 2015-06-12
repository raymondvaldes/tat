/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		        |
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
#include <fstream>
#include <iomanip>
#include "thermal/model/two_dim/analytical_2009/heat2DAna.hpp"
#include "thermal/model/one_dim/numerical_2011/Numerical_Setup.h"
#include "thermal/simulations/Numerical_PhaseOfEmission.h"
#include "math/utility.hpp"
#include "math/numIntegration/simpsons_3_8.hpp"
#include "thermal/define/lthermal.h"

#include <gsl/gsl_sf_bessel.h>


inline void vector3DSetup(std::vector< std::vector< std::vector< double > > > &Vnew,
                   const size_t x, const size_t y, const size_t z) noexcept
{
  Vnew.resize(x);
  for(size_t i = 0; i < x ; ++i )
  {
    Vnew[i].resize(y);

    for(size_t j = 0; j < y ; ++j)
    {
       Vnew[i][j].resize(z);
    }
  }
  return;
}

HeatModel2DAna::HeatModel2DAna( const double R0_, const double R1_,
                                const double lambda_, const double It_,
                                const double , const double asub_,
                                const double gamma_, const double beam_,
                                const double k_coat_, const double L_,
                                const double psi_coat_, const double ccoat_,
                                const double lambda_Sub_,
                                const class numericalModel::Mesh mesh_ ) noexcept
  : R0(R0_), R1(R1_), lambda(lambda_), It(It_), asub(asub_),
    gamma(gamma_), beam(beam_), k_coat(k_coat_), L(L_), psi_coat(psi_coat_),
    ccoat(ccoat_), lambda_Sub(lambda_Sub_), mesh(mesh_)
{
  if(R0_ < 0 || R0_ > 1 || R1_ < 0 || R1_ > 1 || lambda_ < 0)
  {
    std::cout << "\ninput errors in radJ2" << R0_ <<"\t" << R1_ << "\t";
    std::cout << lambda_<< "\n";
    exit(-99);
  }

  funcComplex = new std::complex<double>[nuSize] ;
  funcComplexR = new std::complex<double>[nuSize * mesh.Rend] ;
  funcComplexZ = new std::complex<double>[nuSize * mesh.M2] ;
  nuSpace = new double[nuSize] ;

  funcReal = new double[nuSize] ;
  funcImag = new double[nuSize] ;

  math::range( nuSpace, nuStart, nuEnd, nuSize ) ;
}

HeatModel2DAna::~HeatModel2DAna(void) noexcept
{
  cleanup();
}


void HeatModel2DAna::cleanup(void) const noexcept
{
  delete[] funcComplex;
  delete[] funcComplexR;
  delete[] funcComplexZ;
  delete[] nuSpace;

  delete[] funcReal;
  delete[] funcImag;
}

double HeatModel2DAna::radJ0(void) const noexcept
{
  /* Radiosity J0 is the flux into the coating from the top surface */
  const double product =  R0 * R1 * exp(-2./lambda);
  return 1 + product / (1.- product);
}

double HeatModel2DAna::radJ1(void) const noexcept
{
  /* Radiosity J1 is the flux into the coating from the interface */
  double
  radiosity  = R1 * exp(-1./lambda);
  radiosity /= 1 - R0 * R1 * exp(-2./lambda);

  return radiosity;
}

double HeatModel2DAna::radJ2(void) const noexcept
{
  /* Radiosity J2 is the flux into the substrate from the interface */
  double
  radiosity  = 1;
  radiosity -= R1;

  radiosity *= exp(-1./lambda);
  radiosity /= 1 - R0 * R1 * exp(-2./lambda);

  return radiosity;
}

double HeatModel2DAna::gSpatial(const double zNorm) const noexcept
{
  /*
  zNorm is the axial spatial parameter of the volumetric heating
  distribution.  Care must be taken to ensure that zNorm is normalized
  for the coating thickness
  */
  BOOST_ASSERT(zNorm >= 0);

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
  return 0;
}

std::complex<double> HeatModel2DAna::nuTilde(const double nu,
                                             const double ltherm) const noexcept
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
                                           const double ltherm) const noexcept
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
                                           const double ltherm ) const noexcept
{
  const std::complex<double> nuHAT = nuHat(nu, ltherm);
  const std::complex<double> nuTIlde = nuTilde(nu, ltherm);

  return fFunc(ltherm,nuHAT,nuTIlde );
}

std::complex<double> HeatModel2DAna::fFunc(const double ltherm,
                                           const std::complex<double> nuHAT,
                                           const std::complex<double> nuTIlde)
                                           const noexcept
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
                                           const double z) const noexcept
{
  const std::complex<double> nuHAT = nuHat(nu, ltherm);
  const std::complex<double> nuTIlde = nuTilde(nu, ltherm);
  return HFunc(ltherm, z, nuHAT ,nuTIlde );
}

std::complex<double>
HeatModel2DAna::HFunc(const double ltherm, const double zNorm,
                      const std::complex<double> nuHAT,
                      const std::complex<double> nuTIlde) const noexcept
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
  retrn2b = fFunc(ltherm, nuHAT, nuTIlde);
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
                           const double zNorm) const noexcept
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
  retrn3 = HFunc(ltherm, zNorm, nuHAT, nuTIlde);
  retrn3 *= exp( -1 / lambda );
  retrn3 /=  1 - R0 * R1 * exp( -2 / lambda );

  std::complex<double>
  retrn4a  =  nuTIlde;
  retrn4a *= zNorm;
  retrn4a /= ltherm;

  std::complex<double>
  retrn4b  = fFunc(ltherm, nuHAT, nuTIlde);
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
                                const double zNorm) const noexcept
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
                        const noexcept
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
  sumReal = math::numIntegration::simpson_3_8(funcReal, nuSpace, xlow, xhigh);

  const double
  sumImag = math::numIntegration::simpson_3_8(funcImag, nuSpace, xlow, xhigh);

  ///Cleanup
  const std::complex<double> sum (sumReal, sumImag);
  return sum;
}

std::complex<double>
HeatModel2DAna::theta(const double r, const double z, const double ltherm) const noexcept
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
                             const double ltherm) const noexcept
{
  return theta(r, z, ltherm) * ( L * It * ( 1 - R0 ) / k_coat );
}

double
HeatModel2DAna::TempT(const double r, const double z, const double tau_,
                      const double omega) const noexcept
{
  /*
  The transient temperature (real). The parameters are normalized
  including time.
  */
  const double ltherm = thermal::define::lthermal(L, k_coat, psi_coat, omega);
  constexpr std::complex<double> _i_ (0.0, 1.0);

  std::complex<double>
  TempComplex = TempTComplex(r, z, ltherm);
  TempComplex *= exp(_i_ * 2. * M_PI * tau_);

  return real(TempComplex);
}

std::complex<double>
HeatModel2DAna::iHankel(const size_t r, const size_t z) const noexcept
{
  for(size_t n = 0; n < nuSize ;  ++n)
  {
    funcComplex[n]  = funcComplexZ[z + n*mesh.M2];
    funcComplex[n] *= funcComplexR[r + n*mesh.Rend];

    funcReal[n] = funcComplex[n].real();
    funcImag[n] = funcComplex[n].imag();
  }

  ///Integrate each one independently
  const size_t xlow =  0;
  const size_t xhigh = nuSize - 1;


  return math::numIntegration::simpson_3_8Complex(funcReal, funcImag ,nuSpace,xlow,xhigh);
}

void
HeatModel2DAna::TemperatureDistro(std::vector<std::vector<std::vector<double>>>
                                  &Temperature, const double omega) const noexcept
{
  ///Determine the thermal penetration based on the omega
  using thermal::define::lthermal;
  const double ltherm = lthermal(L, k_coat, psi_coat, omega);
  constexpr   std::complex<double> _i_ (0.0, 1.0);

  ///Populate working arrays
  CPLXWorkingArrays(ltherm);

  ///Implement with working arrays
  for(size_t r = 0; r < mesh.Rend; ++r)
  {
    for(size_t z = 0; z < mesh.M2; ++z)
    {
      const std::complex<double> TempTComplexSol =
      iHankel(r, z) * ( L * It * ( 1 - R0 ) / k_coat );

      for(size_t n = 0; n < mesh.Nend; ++n)
      {
        const std::complex<double> TempTComplexI =
        TempTComplexSol * exp( _i_ * 2. * M_PI * mesh.tau[n] );

        Temperature[n][r][z]  = real(TempTComplexI);
      }
    }
  }

}

void
HeatModel2DAna::TemperaturePrintOut(const std::string dir, const double L_coat)
                                    const noexcept
{
  /// Setup Temperature[n][r][z] Vector
  std::vector< std::vector< std::vector< double > > > T2DProfile;
  vector3DSetup(T2DProfile, mesh.Nend, mesh.Rend, mesh.M2);

  for(size_t n = 0; n < mesh.Nend; ++n)
  {
    std::ofstream myfile;
    std::stringstream filename;
    filename << dir  << "/" <<"../data/T2DProfile/T" << n <<".dat";
    myfile.open(filename.str().c_str());
    myfile << std::setprecision(8);

    for(size_t i = 0; i < mesh.Rend; ++i)
    {
      for(size_t j = 0; j < mesh.M2; ++j)
      {
        if(j <= mesh.M1)
        {
          myfile << mesh.zNorm2[j] << "\t" ;
          myfile << mesh.rReal[i] / L_coat << "\t";
          myfile << T2DProfile[n][i][j] << "\n";
        }
        else if(j > mesh.M1)
        {
          myfile << mesh.zNorm2[j] << "\t" ;
          myfile << mesh.rReal[i] / L_coat << "\t";
          myfile << T2DProfile[n][i][j] << "\n";
        }
      }
    }
    myfile.close();
  }
}

void
HeatModel2DAna::CPLXWorkingArrays(const double ltherm) const noexcept
{
  ///workspaces
  for(size_t n = 0 ; n < nuSize; ++n)
  {
    const double nu = nuSpace[n];
    for(size_t z = 0; z < mesh.M2; ++z)
    {

      if(z <= mesh.M1)
      {
        funcComplexZ[z + n*mesh.M2] = hTildeCoat( nu, ltherm, mesh.zNorm2[z]);

      }
      else if(z > mesh.M1 && z < mesh.M2)
      {
        funcComplexZ[z + n*mesh.M2] = hTildeSubstrate(nu, ltherm, mesh.zNorm2[z]);
      }
    }

    for(size_t r = 0; r < mesh.Rend; ++r)
    {
      funcComplexR[r + n*mesh.Rend] =
      gsl_sf_bessel_J0( nu * mesh.rNorm[r] ) * nu;
    }
  }
}



void HeatModel2DAna::testing(void) const noexcept
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
            std::cout << std::setprecision(precO) << fFunc(nu,ltherm) << "\n";
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
