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
#ifndef NUMERICAL_SETUP_H_INCLUDED
#define NUMERICAL_SETUP_H_INCLUDED

#include "thermal/analysis/kernal.hpp"

double gspatial(double eta, double opt, double lambda, double R1,
                double Iplus0, double Iplus1);

void solveMatrix(const size_t n, const std::vector<double>& b,
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



#endif // NUMERICAL_SETUP_H_INCLUDED
