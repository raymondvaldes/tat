/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |        
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  						|
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
#ifndef EXPERIMENTAL_PHASEOFEMISSION_H_INCLUDED
#define EXPERIMENTAL_PHASEOFEMISSION_H_INCLUDED

#include "models/poptea.hpp"

double Experimental_PhaseOfEmission(double*phase, const size_t L_end);
void phase99(const thermalAnalysisMethod::PopTea &poptea,
             double *Numerical_Phase);
void phase99(const thermalAnalysisMethod::PopTea &poptea,
             std::vector<double> &arrayVal);

#endif // EXPERIMENTAL_PHASEOFEMISSION_H_INCLUDED
