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
#include <cmath>
#include <boost/assert.hpp>

#include "thermal/emission/phase99.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/simulations/Numerical_PhaseOfEmission.h"
#include "thermal/model/one_dim/analytical_2005/analytical_2005.h"

using std::vector;
using std::cout;
using std::pair;
using thermal::analysis::Kernal;

namespace thermal{
namespace emission{


vector<double>
phase99( const Kernal &popteaCore,
         const vector<double> &omegas )
{
  /*The phase for each thermal penetration is calculated in parallel using the
  OpenMP framework.  This gives significant increases in the speed of the code
  for all ranges of L_end.  This also allows the code to be parallelized at
  a very high level. No further modifications of the code is necessary.*/

  const size_t L_end = omegas.size() ;
  vector<double> results(L_end) ;

  switch( popteaCore.thermalsys.Construct.heat )
  {
    case define::HeatX::OneDimAnalytical:
    {
      using thermal::model::one_dim::analytical_2005;
      const analytical_2005 thermalEngine( popteaCore.TBCsystem.coating,
                                           popteaCore.TBCsystem.substrate,
                                           popteaCore.TBCsystem.optical,
                                           popteaCore.expSetup.laser,
                                           popteaCore.TBCsystem.Temp.rear,
                                           popteaCore.TBCsystem.gammaEval() ) ;
      results = thermalEngine.sweep_phase_linear( omegas ) ;
      break;
    }

    case define::HeatX::OneDimNumLin:
    {
      size_t n = 0;
      #pragma omp parallel for schedule(dynamic) private(n)
      for(n = 0 ; n < L_end ; n++ )
          { results[n] = PhaseOfEmission1DNum( omegas[n] , popteaCore ) ; }
      break;
    }

    case define::HeatX::TwoDimAnalytical:
    {
      size_t n = 0;
      #pragma omp parallel for schedule(dynamic) private(n)
      for(n = 0 ; n < L_end ; n++ )
        { results[n] = PhaseOfEmission2DAna( omegas[n], popteaCore ) ; }
      break;
    }

    case define::HeatX::OneDimNumNonLin:
      cout << "no model available"; exit(-2);
    case define::HeatX::TwoDimNumLin:
      cout << "no model available"; exit(-2);
    case define::HeatX::TwoDimNumNonLin:
      cout << "no model available"; exit(-2);
    default:
      cout << "no model available"; exit(-2);
  }

  for( const auto val : results ) {
    using std::isnormal;
    BOOST_ASSERT( isnormal( val ) ) ;
  }
  
  return results;
}

vector<double> phase99Pertrub(
  const Kernal &popteaCore,
  const vector<double> &omegas,
  const vector< pair < enum model::labels::Name, double > > list )
{
  Kernal popteaPerturb( popteaCore );
  
  for( auto val: list ) {
    popteaPerturb.updateFromList( val.first, val.second ) ;
  }

  return phase99( popteaPerturb, omegas ) ;
}

}}
