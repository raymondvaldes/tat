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
#ifndef SENSITIVITY_ANALYSIS_HPP
#define SENSITIVITY_ANALYSIS_HPP

//#include "numSimulations/Numerical_Temperature.h"
//#include "numSimulations/Numerical_Setup.h"
//#include "numSimulations/Numerical_PhaseOfEmission.h"
//#include "numSimulations/Numerical_PhaseOfEmission_Results.h"
//#include "algorithms/statistical_tools.hpp"
//#include "algorithms/ThermalProp_Analysis.h"

#include <vector>
#include <cstring>
#include "thermal/analysis/poptea.hpp"

void fitting(class thermal::analysis::Poptea poptea, double *xInitial,
             const size_t interants, const double factorMax,
             const double factorScale);

double evaluateUncertainty(const double MSEarea, double* perturbationTable,
                           const std::vector<double>& calibrationTable,
                           size_t xnum);

#endif // SENSITIVITY_ANALYSIS_HPP
