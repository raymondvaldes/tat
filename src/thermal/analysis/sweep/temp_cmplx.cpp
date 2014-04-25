/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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

#include "thermal/analysis/sweep/temp_cmplx.h"
#include "thermal/model/one_dim/analytical_2005/analytical_2005.h"

namespace thermal{
namespace analysis{
namespace sweep{

std::vector< std::complex<double> >
temp_cplx_99( const thermal::analysis::Kernal &popteaCore,
              const double omega )
{
  /*The result for each thermal penetration is calculated in parallel using the
  OpenMP framework.  This gives significant increases in the speed of the code
  for all ranges of L_end.  This also allows the code to be parallelized at
  a very high level. No further modifications of the code is necessary.*/
  using std::vector;
  using std::complex;

  
  /* A fine mesh will be used to report back the complex temperature.  This 
  will differ from the mesh used in the numerical solution for now.*/
  constexpr size_t M1 = 200;
  vector< complex<double> > results( M1 ) ;

  switch( popteaCore.thermalsys.Construct.heat )
  {
    case define::HeatX::OneDimAnalytical:
    {
      using thermal::model::one_dim::analytical_2005;
      const analytical_2005 thermalEngine( popteaCore.TBCsystem.coating,
                                           popteaCore.TBCsystem.optical,
                                           popteaCore.expSetup.laser,
                                           popteaCore.TBCsystem.Temp.rear,
                                           popteaCore.TBCsystem.gammaEval());
//      results = thermalEngine.phase_linear( omega ) ; }
      complex<double> temp = thermalEngine.T_tt_eval_cplx( omega, 0 );
      results[0] = temp;
      
      
      
      break;
    }

    case define::HeatX::OneDimNumLin:
    {
//      size_t n = 0;
//      #pragma omp parallel for schedule(dynamic) private(n)
//      for(n = 0 ; n < L_end ; n++ )
//          { results[n] = PhaseOfEmission1DNum( omegas[n] , popteaCore ) ; }
      break;
    }

    case define::HeatX::TwoDimAnalytical:
    {
//      size_t n = 0;
//      #pragma omp parallel for schedule(dynamic) private(n)
//      for(n = 0 ; n < L_end ; n++ )
//        { results[n] = PhaseOfEmission2DAna( omegas[n], popteaCore ) ; }
      break;
    }

    case define::HeatX::OneDimNumNonLin:
      std::cout << "no model available"; exit(-2);
    case define::HeatX::TwoDimNumLin:
      std::cout << "no model available"; exit(-2);
    case define::HeatX::TwoDimNumNonLin:
      std::cout << "no model available"; exit(-2);
    default:
      std::cout << "no model available"; exit(-2);
  }

  return results;
}



}}}