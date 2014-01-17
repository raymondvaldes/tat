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
#ifndef THERMAL_MODELS_H_INCLUDED
#define THERMAL_MODELS_H_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/list_inserter.hpp>
#include <gsl/gsl_sf.h>
#include "models/numericalmodel.hpp"

class HeatModel2DAna
{
public:
  explicit HeatModel2DAna(const double R0_, const double R1_, const double lambda_,
                 const double It_, const double csub_, const double asub_,
                 const double gamma_, const double beam_, const double k_coat,
                 const double L_, const double psi_coat_, const double ccoat_,
                 const double lambda_Sub_,
                 const class numericalModel::Mesh mesh_);

  ~HeatModel2DAna(void);
  void TemperatureDistro(std::vector< std::vector< std::vector< double > > >
                         &Temperature,const double omega) const;
  void TemperaturePrintOut(const std::string dir, const double L_coat) const;
  void testing(void) const;

private:
  const double R0, R1, lambda, It, csub, asub, gamma, beam;
  const double k_coat, L, psi_coat, ccoat, lambda_Sub;
  const class numericalModel::Mesh mesh;

  const double epsabs = 1e-4;
  const double epsrel = 1e-4;

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
  double radJ0(void) const;
  double radJ1(void) const;
  double radJ2(void) const;
  double gSpatial(const double zNorm) const;
  std::complex<double> nuTilde(const double nu, const double ltherm) const;
  std::complex<double> nuHat(const double nu, const double ltherm) const;
  std::complex<double> fFunc(const double nu, const double ltherm ) const;
  std::complex<double> fFunc(const double ltherm,
                             const std::complex<double> nuHAT,
                             const std::complex<double> nuTIlde ) const;
  std::complex<double> HFunc(const double nu, const double ltherm,
                             const double zNorm) const;
  std::complex<double> HFunc(const double ltherm,
                             const double zNorm,
                             const std::complex<double> nuHAT,
                             const std::complex<double> nuTIlde) const;
  std::complex<double> hTildeCoat(const double nu, const double ltherm,
                                  const double zNorm) const;
  std::complex<double> hTildeSubstrate(const double nu, const double ltherm,
                                       const double zNorm) const;
  std::complex<double> iHankel(std::complex<double>(HeatModel2DAna::*hfunc)
                              (const double, const double, const double)const,
                               const double rNorm, const double zNorm,
                               const double ltherm)const;
  std::complex<double> iHankel(const size_t r, const size_t z) const;
  void CPLXWorkingArrays(const double ltherm) const;
  std::complex<double> TempTComplex(const double rNorm, const double zNorm,
                                    const double ltherm) const;
  std::complex<double> theta(const double r, const double z,
                             const double ltherm) const;
  double TempT(const double rNorm, const double zNorm, const double tau,
               const double omega) const;
  void cleanup(void) const;
};

class Emission
{
public:
  explicit Emission(const double detector_lam_, const double T_ref_,
           const class numericalModel::Mesh mesh, const double beamR_,
           const double E_sigma_);
  ~Emission();
  double phase2D(std::vector< std::vector< std::vector< double > > >
                         &Temperature) const;
  double phase1D(const class Temperature Tprofile) const;

private:
  mutable double *Ib;
  mutable double *EmissionTime;

  const double detector_lam, T_ref;
  const class numericalModel::Mesh mesh;
  const double beamR, E_sigma;

  double mean(const double x1, const double x2) const;
  double drArea(const double r0_, const double r1_) const;
  double Ib_plank(const double Temperature) const;
  double emissionAxial(std::vector<double> &Temperature) const;
  double emissionAxial(const class Temperature Tprofile, const size_t nVal)
  const;

  double emissionAxialLinear(std::vector<double> &Temperature) const;
  double emissionVolumetric2D(std::vector<std::vector<double>>&Temperature)
  const;
};

namespace thermal{

double effusivity(const double k, const double rhoCp);
double diffusivity(const double k, const double rhoCp);

enum class HeatX: uint8_t
{
  OneDimAnalytical,
  OneDimNumLin,
  OneDimNumNonLin,
  TwoDimAnalytical,
  TwoDimNumLin,
  TwoDimNumNonLin
};

typedef boost::bimap< enum HeatX , std::string > HeatXBiTYPE;
const HeatXBiTYPE HeatXMap =
    boost::assign::list_of < HeatXBiTYPE::relation >
 ( HeatX::OneDimAnalytical , "OneDimAnalytical")
 ( HeatX::OneDimNumLin     , "OneDimNumLin")
 ( HeatX::OneDimNumNonLin  , "OneDimNumNonLin")
 ( HeatX::TwoDimAnalytical , "TwoDimAnalytical")
 ( HeatX::TwoDimNumLin     , "TwoDimNumLin")
 ( HeatX::TwoDimNumNonLin  , "TwoDimNumNonLin");


enum class EmissionX: uint8_t
{
  OneDimNonLin,
  TwoDimNonLin
};

typedef boost::bimap < enum EmissionX , std::string > emission_bimap;
const emission_bimap EmissionXMap = \
    boost::assign::list_of < emission_bimap::relation >
 ( EmissionX::OneDimNonLin , "OneDimNonLin")
 ( EmissionX::TwoDimNonLin , "TwoDimNonLin");


class ThermalModelSelection
{

public:
  size_t iter;
  const enum HeatX heat;
  const enum EmissionX emission;
  class numericalModel::Mesh mesh;

  explicit ThermalModelSelection(const enum HeatX myHeat,
                                 const enum EmissionX myEmission,
                                 class numericalModel::Mesh mesh_);
  static class ThermalModelSelection
      loadConfigfromXML(const boost::property_tree::ptree pt,
                        const class numericalModel::Mesh mesh_);
  ~ThermalModelSelection(void);
};

}



#endif // THERMAL_MODELS_H_INCLUDED
