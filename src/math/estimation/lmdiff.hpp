/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef LMDIFF_HPP
#define LMDIFF_HPP

#include "math/estimation/settings.h"

namespace math{
  namespace estimation{

void lmdif(void (*fcn)(int, int, double*, double*, int*, double**), int m,
           int n, double *x, double *fvec, double **variables, double ftol,
           double xtol, double gtol, int maxfev, double epsfcn, double *diag,
           int mode, double factor, int nprint, int *info, int *nfev,
           double *fjac, int ldfjac, int *ipvt, double *qtf, double *wa1,
           double *wa2, double *wa3, double *wa4, double *) noexcept;

void lmdif(std::function < void ( double*, double* ) > fcn,
            int m, int n, double *x, double *fvec, double ftol, double xtol,
            double gtol, int maxfev, double epsfcn, double *diag, int mode,
            double factor, int nprint, int *info, int *nfev, double *fjac,
            int ldfjac, int *ipvt, double *qtf, double *wa1, double *wa2,
            double *wa3, double *wa4) noexcept;

void lmdif(std::function < void ( double*, double* ) > fcn,
            const size_t dataPoints, std::vector<double>& initialConditions,
            const settings &Settings) noexcept;

  }
}


#endif // LMDIFF_HPP
