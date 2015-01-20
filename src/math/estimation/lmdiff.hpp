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
#ifndef LMDIFF_HPP
#define LMDIFF_HPP

#include "thermal/analysis/kernal.hpp"

namespace math{
  namespace estimation{

void lmdif(void (*fcn)(int, int, double*, double*, int*, double**), int m,
           int n, double *x, double *fvec, double **variables, double ftol,
           double xtol, double gtol, int maxfev, double epsfcn, double *diag,
           int mode, double factor, int nprint, int *info, int *nfev,
           double *fjac, int ldfjac, int *ipvt, double *qtf, double *wa1,
           double *wa2, double *wa3, double *wa4, double *) noexcept;


void fdjac2(void (*fcn)(int, int, double*, double*, int*,double **),
            int m,int n,double x[],double fvec[],double **variables,
            double fjac[],int ldfjac, int *iflag,double epsfcn,double wa[]) noexcept;


double enorm(int n,double x[])noexcept ;

int mod(int k,int m) noexcept;

double dmin1(double a,double b)noexcept;

int min0(int a,int b)noexcept;

void pmat(int m,int n,double y[])noexcept;

void qrfac( const int m, const int n, double a[], int /*lda*/, const bool pivot,
            int ipvt[], int /*lipvt*/, double rdiag[], double acnorm[],
            double wa[] ) noexcept;
    
double dmax1(double a,double b) noexcept;

void lmpar( const int n, double *r, const int ldr, const int *ipvt,
            const double *diag, double *qtb, const double delta, double *par,
            double *x, double *sdiag, double *wa1, double *wa2 ) noexcept;
    
//void qrsolv(int n,double r[],int ldr,int ipvt[],double diag[],double qtb[],
//            double x[],double sdiag[],double wa[]);

void qrsolv( const int n,  double r[], const int ldr, const int ipvt[],
              const double diag[], const double qtb[],  double x[], double sdiag[],
               double wa[] ) noexcept;



void fdjac2(std::function<void( double*, double* )> fcn,
            int m, int n, double x[], double fvec[], double fjac[], int /*ldfjac*/,
            int *iflag, double epsfcn, double wa[]) noexcept;

void lmdif(std::function < void ( double*, double* ) > fcn,
            int m, int n, double *x, double *fvec, double ftol, double xtol,
            double gtol, int maxfev, double epsfcn, double *diag, int mode,
            double factor, int nprint, int *info, int *nfev, double *fjac,
            int ldfjac, int *ipvt, double *qtf, double *wa1, double *wa2,
            double *wa3, double *wa4) noexcept;


void lmdif(std::function < void ( double*, double* ) > fcn,
            int dataPoints, std::vector<double>& initialConditions,
            const settings &Settings) noexcept;


  }
}


#endif // LMDIFF_HPP
