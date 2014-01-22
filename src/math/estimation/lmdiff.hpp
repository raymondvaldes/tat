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
           double *wa2, double *wa3, double *wa4, double *);

void lmdif(void (*fcn)(int, int, double*, double*, int*,
                       class thermalAnalysis::Kernal),
           int m, int n, double *x, double *fvec,double ftol, double xtol,
           double gtol, int maxfev, double epsfcn, double *diag, int mode,
           double factor, int nprint, int *info, int *nfev, double *fjac,
           int ldfjac, int *ipvt, double *qtf, double *wa1, double *wa2,
           double *wa3, double *wa4, double *wa5,
           class thermalAnalysis::Kernal poptea);

  }
}


#endif // LMDIFF_HPP
