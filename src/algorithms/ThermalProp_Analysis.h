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
#ifndef THERMALPROP_ANALYSIS_H_INCLUDED
#define THERMALPROP_ANALYSIS_H_INCLUDED

#include <boost/foreach.hpp>

#include "math/estimation/parameterestimation.hpp"
#include "thermal/analysis/kernal.hpp"
#include "numSimulations/Numerical_Setup.h"
#include "algorithms/ThermalProp_Analysis.h"

int paramter_estimation( const size_t m, const size_t  n,
                         class math::estimation::settings ParaEstSetting,
                         int *info, int *nfev,
                         double *x, class thermal::analysis::Kernal popteaCore,
                         const double factorMax, const double factorScale,
                         double *xpredicted);

std::vector<double>
paramter_estimation(class thermal::analysis::Kernal popteaCore, int *info,
                    int *nfev);

void ThermalProp_Analysis(int, int N, double*x, double*fvec, int*,
                          class thermal::analysis::Kernal popteaCore );

void printPEstimates( class thermal::analysis::Kernal popteaCore ) ;
void printfJac(const size_t N, const size_t P, const double*fjac);
void InformationIndexAll(const size_t P, const size_t N,
                         const class thermal::analysis::Kernal popteaCore);

void InformationIndex(const size_t P, double *Index,
                      const size_t I, const double ki, const double *const fjac);

void InformationIndex(const size_t P, std::vector<double> Index,
                      const size_t I, const double ki,
                      const double* fjac);

#endif // THERMALPROP_ANALYSIS_H_INCLUDED
