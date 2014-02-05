/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
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
#include <string>
#include <functional>

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/methods.hpp"
#include "thermal/analysis/pie.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "models/physicalmodel.hpp"
#include "math/algorithms/combinations.hpp"
#include "math/utility.hpp"

namespace thermal{
namespace analysis{

methods::methods(
    const math::estimation::settings &Settings_in,
    const math::estimation::unknownList &unknownParameters_in,
    const ThermalData& thermalData_in ,
    const math::estimation::unknownList &thermalSweepSearch ,
    const std::vector<physicalModel::labels> sweepOptimizationGoal)
  : bestfitMethod( new LMA( Settings_in, unknownParameters_in,
                            thermalData_in.size() ) ),
    intervalEstimates( new PIE() ),
    lthermalSweepOptimizer(
      new ThermalSweepOptimizer( Settings_in, thermalSweepSearch,
                                 sweepOptimizationGoal ) )
{}

double methods::bestFit(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  bestfitMethod->solve( list_in, thermalData_in, coreSystem_in );
  return thermalData_in->MSE;
}

void methods::parameterIntervalEstimates(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  intervalEstimates->solve( list_in, thermalData_in, coreSystem_in,
                            bestfitMethod );
}

void methods::optimization(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{

//  lthermalSweepOptimizer->start( list_in, thermalData_in, coreSystem_in,
//                                 bestfitMethod, intervalEstimates ) ;

}











}}
