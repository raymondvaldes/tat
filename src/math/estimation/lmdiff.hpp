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
            int dataPoints, std::vector<double>& initialConditions,
            const settings &Settings) noexcept;


  }
}


#endif // LMDIFF_HPP
