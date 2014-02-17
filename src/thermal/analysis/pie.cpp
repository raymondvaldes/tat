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
#include <utility>
#include "thermal/analysis/pie.hpp"
#include "math/algorithms/combinations.hpp"
//#include "math/estimation/utils.hpp"

namespace thermal{
namespace analysis{

PIE::PIE( void )
{ }

PIE::~PIE(){}

std::string PIE::PIEAnalysisOutput::SearchData::pprint( void )
{
  std::ostringstream output ;

  output << "%*-----------------------------------------*\n" ;
  output << "%| Search Path for PIE Analysis:           |\n" ;
  output << "%|-----------------------------------------|\n" ;
  output << "%| xSet    Quality-of-fit                  |\n" ;

  output.setf( std::ios::fixed, std::ios::floatfield ) ;
  output << std::setprecision(3) ;
  for( const std::pair< double, ThermalData > & pair : allThermalData )
  {
    output << pair.first << "\t"
           << pair.second.MSE << "\n";
  }
  output << "%*-----------------------------------------*\n" ;

  return output.str() ;
}

double PIE::bestFit()
{
  bestfitMethod->solve( unknownParameters, thermalData, coreSystem );
  return thermalData->MSE;
}


PIE::PIEAnalysisOutput::SearchData PIE::PIEAnalysisOutput::
retrieveSearchData( const physicalModel::labels::Name input )
{
  SearchData myOutput;

  for( const SearchData&val : searchPath )
  {
    if( input == val.param )
    {
      myOutput = val;
      break;
    }
  }

  return myOutput;
}

std::string PIE::PIEAnalysisOutput::
prettyPrintSearchPath( const physicalModel::labels::Name input )
{
  SearchData myData = retrieveSearchData( input );
  const std::string output = myData.pprint() ;

  return output;
}


void PIE::PIEAnalysisOutput::clear( void )
{
  searchPath.clear();
}

PIE::PIEAnalysisOutput 
PIE::solve( const std::shared_ptr<math::estimation::unknownList> &list_in,
            const std::shared_ptr<ThermalData> &thermalData_in,
            const std::shared_ptr<Kernal> &coreSystem_in, 
            const std::shared_ptr<LMA> bestfitMethod_in )
{
  ouputResults.clear();

  unknownParameters = list_in ;
  thermalData = thermalData_in ;
  coreSystem = coreSystem_in ;
  bestfitMethod =  bestfitMethod_in ;

  bestFit();
  parameterIntervalEstimates();

  return ouputResults;
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
    (*unknownParameters)( newListVect ) ;

    //std::cerr << "this better be zero = " << Gfunc( bestfit , mylabel )<<"\n";
    constexpr double tol  = 1e-12;
  assert( std::fabs( Gfunc( bestfit , mylabel ) )  < tol ) ;
    const double min = solveFORx( S1, lowerbound, bestfit , mylabel, "min" ) ;
    const double max = solveFORx( S1, bestfit, upperbound , mylabel, "max" ) ;

    originalListParams[i].bestfitIntervalset( min, max) ;


    ///save search data for later analysis
    dataTempStorage.param = mylabel ;        
    ouputResults.searchPath.push_back( dataTempStorage ) ;
    dataTempStorage.allThermalData.clear();

    ///iterate
    i++;
  }

  ///Update list of parameters with updated list
  (*unknownParameters)( originalListParams );

  reloadExperimental();
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
  SAVEpredictions = thermalData_in.predictedEmission;
  SAVEomega = thermalData_in.omegas;
}

void PIE::reloadExperimental( void )
{
  thermalData->experimentalEmission = SAVEExperimental;
  thermalData->predictedEmission = SAVEpredictions;
  thermalData->omegas = SAVEomega;
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

  std::pair<double, ThermalData> saveThis( val, *thermalData ) ;
  dataTempStorage.allThermalData.push_back( saveThis ) ;

  return thermalData->MSE;
}


}}
