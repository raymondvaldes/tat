/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		        |
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
#include <cmath>
#include <cstddef>
#include "math/estimation/utils.hpp"

namespace math{
namespace estimation{
  
double SobjectiveLS( const std::vector<double>& emissionExp ,
                     const std::vector<double>& emissionEst ) noexcept
{
  /*
   The objective function is evaluated for all the measurements.
   emissionEst[n]  ...     is calculated through the model
   emissionExp[n]  ...     is determined through the experiment
   */

  using std::abs;

  double fvec_objective = 0 ;
  
  for( size_t  n =0 ; n < emissionEst.size() ; ++n )
    fvec_objective += pow( emissionExp[n] - emissionEst[n] , 2 )  ;
  
//  fvec_objective = abs( fvec_objective ) ;
  fvec_objective /= emissionEst.size() ;
  

  return fvec_objective ;
}

}}
