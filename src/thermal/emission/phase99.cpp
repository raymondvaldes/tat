/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                         |
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
#include "algorithms/ThermalProp_Analysis.h"
#include "numSimulations/Numerical_PhaseOfEmission.h"

namespace thermal{
  namespace emission{

void phase99( const class thermal::analysis::Kernal &popteaCore,
              std::vector<double> &arrayVal )
{
  /*The phase for each thermal penetration is calculated in parallel using the
  OpenMP framework.  This gives significant increases in the speed of the code
  for all ranges of L_end.  This also allows the code to be parallelized at
  a very high level. No further modifications of the code is necessary.*/
  const size_t L_end = popteaCore.L_end;
  size_t n = 0;

  if( popteaCore.thermalsys.Construct.heat ==  thermal::HeatX::OneDimNumLin )
  {
    #pragma omp parallel for schedule(dynamic) private(n)
    for(n = 0 ; n < L_end ; n++ )
        { arrayVal[n] = PhaseOfEmission1DNum(n , popteaCore); }
  }

  if( popteaCore.thermalsys.Construct.heat ==  thermal::HeatX::TwoDimAnalytical )
  {
    #pragma omp parallel for schedule(dynamic) private(n)
    for(n = 0 ; n < L_end ; n++ )
      { arrayVal[n] = PhaseOfEmission2DAna(n, popteaCore);}
  }

  if( popteaCore.thermalsys.Construct.heat ==  thermal::HeatX::OneDimAnalytical )
  {
      for(n = 0 ; n < L_end ; n++ )
        { arrayVal[n] = PhaseOfEmission1DAna(n , popteaCore); }
  }

  return;
}

std::vector<double>
phase99( const class thermal::analysis::Kernal &popteaCore)
{
  const size_t n = popteaCore.l_thermal.size();
  std::vector<double> results(n);

  phase99( popteaCore, results );

  return results;
}


  }
}
