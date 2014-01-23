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
#ifndef NUMERICAL_PHASEOFEMISSION_RESULTS_H_INCLUDED
#define NUMERICAL_PHASEOFEMISSION_RESULTS_H_INCLUDED

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_integration.h>
#include "numSimulations/Numerical_PhaseOfEmission_Results.h"

double Print_Emission(const double*phase, const double*num_phase,
                      const double*ana_phase,
                      const double*l_thermal, const size_t L_end);


#endif // NUMERICAL_PHASEOFEMISSION_RESULTS_H_INCLUDED
