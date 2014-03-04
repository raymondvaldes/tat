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
#include <vector>
#include <cstddef>
#include "thermal/emission/phase99.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/simulations/Numerical_PhaseOfEmission.h"

namespace thermal{
namespace emission{

std::vector<double>
phase99( const thermal::analysis::Kernal &popteaCore,
         const std::vector<double> &omegas)
{
  /*The phase for each thermal penetration is calculated in parallel using the
  OpenMP framework.  This gives significant increases in the speed of the code
  for all ranges of L_end.  This also allows the code to be parallelized at
  a very high level. No further modifications of the code is necessary.*/

  const size_t L_end = omegas.size() ;
  std::vector<double> results(L_end) ;

  switch( popteaCore.thermalsys.Construct.heat )
  {
    case thermal::HeatX::OneDimAnalytical:
    {
      const double L_coat = popteaCore.TBCsystem.coating.depth ;
      const double k_c    = popteaCore.TBCsystem.coating.kthermal.offset ;
      const double psi_c  = popteaCore.TBCsystem.coating.psithermal.offset ;
      const double lambda = popteaCore.TBCsystem.coating.lambda;
      const double R1     = popteaCore.TBCsystem.optical.R1;
      const double gamma  = popteaCore.TBCsystem.gammaEval();
      const double Esigma = popteaCore.TBCsystem.optical.Emit1;

      for( size_t n = 0 ; n < L_end ; ++n )
        { results[ n ] = PhaseOfEmission1DAna( omegas[n] , L_coat, k_c, psi_c,
                                               lambda, R1, gamma, Esigma ) ; }
      break;
    }

    case thermal::HeatX::OneDimNumLin:
    {
      size_t n = 0;
      #pragma omp parallel for schedule(dynamic) private(n)
      for(n = 0 ; n < L_end ; n++ )
          { results[n] = PhaseOfEmission1DNum( omegas[n] , popteaCore ) ; }
      break;
    }

    case thermal::HeatX::TwoDimAnalytical:
    {
      size_t n = 0;
      #pragma omp parallel for schedule(dynamic) private(n)
      for(n = 0 ; n < L_end ; n++ )
        { results[n] = PhaseOfEmission2DAna( omegas[n], popteaCore ) ; }
      break;
    }

    case thermal::HeatX::OneDimNumNonLin:
      std::cout << "no model available"; exit(-2);
    case thermal::HeatX::TwoDimNumLin:
      std::cout << "no model available"; exit(-2);
    case thermal::HeatX::TwoDimNumNonLin:
      std::cout << "no model available"; exit(-2);
    default:
      std::cout << "no model available"; exit(-2);
  }









  return results;
}

}}
