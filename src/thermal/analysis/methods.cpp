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
#include "math/estimation/parameterestimation.hpp"
#include "models/physicalmodel.hpp"
#include "math/algorithms/combinations.hpp"

namespace thermal{
namespace analysis{

methods::methods( const math::estimation::settings &Settings_,
                  const math::estimation::unknownList &unknownParameters_,
                  const ThermalData& thermalData_ )
  : bestfitMethod( Settings_, unknownParameters_, thermalData_.omegas.size(),
                   thermalData_ )
{}

double methods::bestFit( Kernal &coreSystem, ThermalData &thermalData )
{
  int nfev;
  int info;

  thermalData = bestfitMethod.paramter_estimation( &info, &nfev, coreSystem,
                                                   thermalData);
  coreSystem.updatefromBestFit( bestfitMethod.unknownParameters() );

  return thermalData.MSE;
}

double methods::Gfunc( const double val ,
                       const enum physicalModel::labels::Name &mylabel,
                       Kernal &coreSystem, ThermalData &thermalData)
{
  coreSystem.TBCsystem.updateVal( mylabel , val );
  coreSystem.TBCsystem.updateCoat();
  bestFit( coreSystem, thermalData );

  return thermalData.MSE;
}

double methods::solve( const double target , const double min,
                       const double max,
                       const enum physicalModel::labels::Name &mylabel,
                       const std::string &bound, Kernal &coreSystem,
                       ThermalData &thermalData )
{
  using std::placeholders::_1;
  const std::function<double(double)>
      myFuncReduced = std::bind( &methods::Gfunc, this , _1 , mylabel,
                                 coreSystem, thermalData ) ;

  const math::solve ojb( myFuncReduced, target, min, max ) ;
  double soln = ojb.returnSoln();

  if(!ojb.pass)
  {
    if( bound == "min" ) soln = min;
    if( bound == "max" ) soln = max;
  }

  return soln;
}

void methods::updateExperimentalData( const std::vector<double> &omegas,
                                      const std::vector<double> &input,
                                      const Kernal &coreSystem,
                                      ThermalData &thermalData )
{
  thermalData.updateOmegas( omegas , coreSystem.TBCsystem.coating );
  thermalData.updateExperimental( input );
  bestfitMethod.updateWorkSpace( input.size() ,
                                 bestfitMethod.unknownParameters.size()  );
}

void methods::parameterIntervalEstimates( Kernal &coreSystem,
                                          ThermalData &thermalData )
{
  /// Save experimental data, quality-of-fit, unknownParameter List
  using math::estimation::unknown;
  std::vector< unknown > originalListParams = bestfitMethod.unknownParameters();
  const std::vector<double> SAVEExperimental = thermalData.experimentalEmission;
  const double S1 = thermalData.MSE;

  /// Update initial guess using bestfits
  for( auto& param : originalListParams)
    { param.Initialset( param.bestfit() ); }

  /// Predicted emission as the new experimental
  const std::vector<double> TEMPemissionExperimental = thermalData.predictedEmission;
  updateExperimentalData( thermalData.omegas , TEMPemissionExperimental,
                          coreSystem, thermalData ) ;



  /// Create list of parameters that must be refitted
  using math::algorithms::combos_minusOne;
  const std::vector< std::vector<  unknown > >
      unknownParaLists = combos_minusOne( originalListParams );

  std::vector< enum physicalModel::labels::Name  > parametersToBeManipulated;
  for ( const auto& unknown : originalListParams )
    { parametersToBeManipulated.push_back( unknown.label() ); }

  /// update list of parameters using unknownIterations
  size_t i = 0;
  for( const auto& updatedListParameters : unknownParaLists )
  {
    bestfitMethod.unknownParameters( updatedListParameters );

    ///identifiy fixed parameter and update search bound
    const class unknown myfixedParameter =  originalListParams[i];
    const enum physicalModel::labels::Name
        mylabel = myfixedParameter.label();
    const double bestfit = myfixedParameter.bestfit();
    const double lowerbound = myfixedParameter.lowerBound();
    const double upperbound = myfixedParameter.upperBound();

    ///search space
    const double min = solve( S1, lowerbound, bestfit , mylabel, "min",
                              coreSystem, thermalData );

    const double max = solve( S1, bestfit, upperbound , mylabel, "max",
                              coreSystem, thermalData );

    originalListParams[i++].bestfitIntervalset( min, max);
  }

  ///Update list of parameters with updated list
  bestfitMethod.unknownParameters( originalListParams ) ;
  updateExperimentalData( thermalData.omegas , SAVEExperimental,
                          coreSystem, thermalData );
  thermalData.MSE = S1;
}

}}
