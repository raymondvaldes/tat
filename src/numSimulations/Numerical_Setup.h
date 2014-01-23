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
#ifndef NUMERICAL_SETUP_H_INCLUDED
#define NUMERICAL_SETUP_H_INCLUDED

#include "algorithms/ThermalProp_Analysis.h"
#include "thermal/analysis/kernal.hpp"

void fdjac2(void (*fcn)(int, int, double *, double *, int *,
                        class thermal::analysis::Kernal popteaCore),
            int m, int n, double x[], double fvec[], double fjac[], int,
            int *iflag, double epsfcn, double wa[],
            class thermal::analysis::Kernal popteaCore);

double gspatial(double eta, double opt, double lambda, double R1,
                double Iplus0, double Iplus1);

void solveMatrix(const int n, const std::vector<double>& b,
                 const std::vector<double>& d, const std::vector<double>& a,
                 const std::vector<double>& C, std::vector<double>& u);

double SOR(double**A, double*b, const size_t M2, double*phi, double omega,
           double error);

double gs_int(const double eta, const double opt, const double lambda,
              const double R1, const double Iplus0, const double Iplus1);

double psi(const double eta, const double psi_layer1, const double psi_layer2);
double psi(const std::vector<std::vector<double>>& T, const double eta,
           const size_t j, const size_t n, const double psi_c,
           const double psi_ref);

double k(const std::vector<std::vector<double>>& T, const double zpos,
         const double k_c, const double k_ref);

double kthermal(const double eta, const double k_layer1, const double k_layer2);

double Kappa(const std::vector<std::vector<double>>& T, const double eta,
             const double eta_j, const size_t j, const size_t n,
             const double k_ref, const int prop_linearity, const double k_c);




double Iheat(double Isteady, double Itransient, double omega, double t) ;//verified

size_t sumVector(const size_t *const vector1,const size_t sizeV);

double Iheat_int(const double Isteady,const double Itransient,
                        const double omega, const double t); //verified

double tau_0(const double omega);
double x_bias(const double Xmean, const double Xstddev);

double omega(const double L_coat, const double l_thermal, const double k_c,
             const double psi_c);

double lthermal(const double L_coat, const double k_c, const double psi_c,
                const double omega);

size_t xINTrandom(const size_t xmin, const size_t xmax);




double percentile(const double xmin, const double xmax, const double x);

class perturbStruct
{
  public:
    size_t pNum;

    size_t xnumber;  //keep this odd
    double spread;
    double lmin1;

    double lmax2;
    double PtolBand;
    const double lminRef = 0.2;
    const double lmaxRef = 0.8;
    const double lmin2 = .6;
    const double lmax1 = lmin1;

    size_t iterates;
    double* xArea;
    double* lmin;
    double* lmax;
    double* temp;
    double* bands;

    explicit perturbStruct(const size_t a, const size_t b, const double c );
    explicit perturbStruct(const size_t a, const size_t b, const double c,
                  const double e, const double h, const size_t i);
    void lThermalMC();
    void lthermalDeterministic();
    void lthermalBands(const double PtolBand1);
    void cleanup();
    void cleanup2();
};

class parameterStr
{
public:
  class thermal::analysis::Kernal *popteaCore;
};


#endif // NUMERICAL_SETUP_H_INCLUDED
