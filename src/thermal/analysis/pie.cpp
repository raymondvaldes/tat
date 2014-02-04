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
#include "thermal/analysis/pie.hpp"
#include "math/algorithms/combinations.hpp"


namespace thermal{
namespace analysis{

PIE::PIE( void )
{ }

PIE::~PIE(){}


double PIE::bestFit()
{
  bestfitMethod->solve( unknownParameters, thermalData, coreSystem );
  return thermalData->MSE;
}


void PIE::solve( const std::shared_ptr<math::estimation::unknownList> &list_in,
                 const std::shared_ptr<ThermalData> &thermalData_in,
                 const std::shared_ptr<Kernal> &coreSystem_in,
                 const std::shared_ptr<LMA> bestfitMethod_in )
{
  unknownParameters = list_in ;
  thermalData = thermalData_in ;
  coreSystem = coreSystem_in ;
  bestfitMethod =  bestfitMethod_in ;

  parameterIntervalEstimates();
}

void PIE::parameterIntervalEstimates( void )
{
  /// Save experimental data, quality-of-fit, unknownParameter List
  using math::estimation::unknown;
  std::vector< unknown > originalListParams( (*unknownParameters)() );
  saveExperimental( *thermalData );
  const double S1 = thermalData->MSE;

  /// Update initial guess using bestfits
  for( auto& param : originalListParams)
    { param.Initialset( param.bestfit() ); }

  /// Predicted emission as the new experimental
  const std::vector<double> TEMPExperimental = thermalData->predictedEmission;
  updateExperimentalData( TEMPExperimental, *thermalData) ;

  /// Create list of parameters that must be refitted
  using math::algorithms::combos_minusOne;
  const std::vector< std::vector<  unknown > >
      unknownParaLists = combos_minusOne( originalListParams );

  std::vector< enum physicalModel::labels::Name  > parametersToBeManipulated;
  for ( const auto& unknown : originalListParams )
    { parametersToBeManipulated.push_back( unknown.label() ); }

  /// update list of parameters using unknownIterations
  size_t i = 0;
  for( auto& newListVect : unknownParaLists )
  {
    ///identifiy fixed parameter and update search bound
    const unknown myfixedParameter =  originalListParams[i];
    const enum physicalModel::labels::Name mylabel = myfixedParameter.label();
    const double bestfit = myfixedParameter.bestfit();
    const double lowerbound = myfixedParameter.lowerBound();
    const double upperbound = myfixedParameter.upperBound();

    ///search space
    (*unknownParameters)( newListVect );
    const double min = solveFORx( S1, lowerbound, bestfit , mylabel, "min" ) ;
    const double max = solveFORx( S1, bestfit, upperbound , mylabel, "max" ) ;

    originalListParams[i++].bestfitIntervalset( min, max);
  }

  ///Update list of parameters with updated list
  (*unknownParameters)( originalListParams );
  updateExperimentalData(  SAVEExperimental, *thermalData ) ;
  thermalData->MSE = S1;
}

double PIE::solveFORx( const double target , const double min, const double max,
                       const enum physicalModel::labels::Name mylabel,
                       const std::string &bound )
{
  const std::function<double(double)>
      myFuncReduced = std::bind( &PIE::Gfunc, this , std::placeholders::_1,
                                 mylabel ) ;

  const math::solve ojb( myFuncReduced, target, min, max ) ;
  double soln = ojb.returnSoln();

  if(!ojb.pass)
  {
    if( bound == "min" ) soln = min;
    if( bound == "max" ) soln = max;
  }

  return soln;
}

void PIE::saveExperimental( const ThermalData& thermalData_in )
{
  SAVEExperimental = thermalData_in.experimentalEmission;
  SAVEomega = thermalData_in.omegas;
}
void PIE::updateExperimentalData( const std::vector<double> &input,
                                  ThermalData &thermalData_in )
{
  thermalData_in.updateExperimental( input );
}
double PIE::Gfunc( const double val ,
                   const enum physicalModel::labels::Name &mylabel)
{
  coreSystem->TBCsystem.updateVal( mylabel , val ) ;
  coreSystem->TBCsystem.updateCoat() ;

  bestFit() ;

  return thermalData->MSE;
}


}}
