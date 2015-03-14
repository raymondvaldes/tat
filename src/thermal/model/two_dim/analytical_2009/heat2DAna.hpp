/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  	        	|
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
#ifndef HEAT2DANA_HPP
#define HEAT2DANA_HPP

#include <complex>

#include "thermal/model/one_dim/numerical_2011/Numerical_Setup.h"
#include "thermal/simulations/Numerical_PhaseOfEmission.h"
#include "math/utility.hpp"
#include "math/numIntegration/simpsons_3_8.hpp"

class HeatModel2DAna
{
public:
  explicit HeatModel2DAna( const double R0_, const double R1_,
                           const double lambda_, const double It_,
                           const double csub_, const double asub_,
                           const double gamma_, const double beam_,
                           const double k_coat, const double L_,
                           const double psi_coat_, const double ccoat_,
                           const double lambda_Sub_,
                           const class numericalModel::Mesh mesh_ ) noexcept;

  ~HeatModel2DAna(void) noexcept;
  void TemperatureDistro( std::vector< std::vector< std::vector< double > > >
                          &Temperature,const double omega) const noexcept;
  void TemperaturePrintOut( const std::string dir, const double L_coat ) const noexcept;
  void testing( void ) const noexcept;

private:
  const double R0, R1, lambda, It, asub, gamma, beam;
  const double k_coat, L, psi_coat, ccoat, lambda_Sub;
  const class numericalModel::Mesh mesh;

  ///nullspace
  const double nuStart = 0;
  const double nuEnd = 7;
  const size_t nuSize = 50;

  ///setup workspaces
  mutable double*funcReal;
  mutable double*funcImag;
  mutable double*nuSpace;
  mutable std::complex<double>*funcComplex ;
  mutable std::complex<double>*funcComplexR;
  mutable std::complex<double>*funcComplexZ;

  ///member functions
  double radJ0(void) const noexcept;
  double radJ1(void) const noexcept;
  double radJ2(void) const noexcept;
  double gSpatial(const double zNorm) const noexcept;
  std::complex<double> nuTilde(const double nu, const double ltherm) const noexcept;
  std::complex<double> nuHat(const double nu, const double ltherm) const noexcept;
  std::complex<double> fFunc(const double nu, const double ltherm ) const noexcept;
  std::complex<double> fFunc(const double ltherm,
                             const std::complex<double> nuHAT,
                             const std::complex<double> nuTIlde ) const noexcept;
  std::complex<double> HFunc(const double nu, const double ltherm,
                             const double zNorm) const noexcept;
  std::complex<double> HFunc(const double ltherm,
                             const double zNorm,
                             const std::complex<double> nuHAT,
                             const std::complex<double> nuTIlde) const noexcept;
  std::complex<double> hTildeCoat(const double nu, const double ltherm,
                                  const double zNorm) const noexcept;
  std::complex<double> hTildeSubstrate(const double nu, const double ltherm,
                                       const double zNorm) const noexcept;
  std::complex<double> iHankel(std::complex<double>(HeatModel2DAna::*hfunc)
                              (const double, const double, const double) const,
                               const double rNorm, const double zNorm,
                               const double ltherm) const noexcept;
  std::complex<double> iHankel(const size_t r, const size_t z) const noexcept;
  void CPLXWorkingArrays(const double ltherm) const noexcept;
  std::complex<double> TempTComplex(const double rNorm, const double zNorm,
                                    const double ltherm) const noexcept;
  std::complex<double> theta(const double r, const double z,
                             const double ltherm) const noexcept;
  double TempT(const double rNorm, const double zNorm, const double tau,
               const double omega) const noexcept;
  void cleanup(void) const noexcept;
};


#endif // HEAT2DANA_HPP
