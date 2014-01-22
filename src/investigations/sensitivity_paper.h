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
#ifndef SENSITIVITY_PAPER_HPP_INCLUDED
#define SENSITIVITY_PAPER_HPP_INCLUDED

#include "numSimulations/Numerical_Setup.h"
#include "numSimulations/Numerical_PhaseOfEmission.h"
#include "algorithms/sensitivity_analysis.hpp"
#include "algorithms/ThermalProp_Analysis.h"

namespace SensitivityValdes2013
{
    void figureSensitivityIntro(class thermal::analysis::Kernal popteaCore);

//    void CC_APS2(class thermal::analysis::Kernal popteaCore);

}

#endif // SENSITIVITY_PAPER_HPP_INCLUDED
