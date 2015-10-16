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

auto lmdif(std::function < void ( double*, double* ) > fcn,
            const size_t dataPoints, std::vector<double>& initialConditions,
            const settings &Settings) noexcept -> int;
    

//*	info is an integer output variable. if the user has
//*	  terminated execution, info is set to the (negative)
//*	  value of iflag. see description of fcn. otherwise,
//*	  info is set as follows.
//*
//*	  info = 0  improper input parameters.
//*
//*	  info = 1  both actual and predicted relative reductions
//*		    in the sum of squares are at most ftol.
//*
//*	  info = 2  relative error between two consecutive iterates
//*		    is at most xtol.
//*
//*	  info = 3  conditions for info = 1 and info = 2 both hold.
//*
//*	  info = 4  the cosine of the angle between fvec and any
//*		    column of the jacobian is at most gtol in
//*		    absolute value.
//*
//*	  info = 5  number of calls to fcn has reached or
//*		    exceeded maxfev.
//*
//*	  info = 6  ftol is too small. no further reduction in
//*		    the sum of squares is possible.
//*
//*	  info = 7  xtol is too small. no further improvement in
//*		    the approximate solution x is possible.
//*
//*	  info = 8  gtol is too small. fvec is orthogonal to the
//*		    columns of the jacobian to machine precision.
//*
  

  }
}


#endif // LMDIFF_HPP
