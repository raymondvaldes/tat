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
#include "tools/interface/exportfile.hpp"
#include "tools/interface/filesystem.hpp"

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

  return output.str() ;
}

void PIE::PIEAnalysisOutput::ThermalSweep::prettyPrint(const std::string folder)
{
  const std::string newFolder = "thermalSweep" ;
  filesystem::makeDir( folder , newFolder ) ;
  const std::string updatedPath = folder + "/" +newFolder ;

  const std::string output1 = bestfit.prettyPrint();
  const std::string output2 = upperbound.prettyPrint();
  const std::string output3 = lowerbound.prettyPrint();

  const std::string path1 =  updatedPath + "/" + "bestfit.dat" ;
  const std::string path2 =  updatedPath + "/" + "upperbound.dat" ;
  const std::string path3 =  updatedPath + "/" + "lowerbound.dat" ;

  tools::interface::exportfile( path1 , output1 ) ;
  tools::interface::exportfile( path2 , output2 ) ;
  tools::interface::exportfile( path3 , output3 ) ;
}


void PIE::PIEAnalysisOutput::SearchData::
  ppThermalSweep ( const std::string folder)
{
  thermalSweep.prettyPrint( folder );
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

  for( const SearchData&data : searchPath )
  {
    if( input == data.param )
    {
      myOutput = data ;
      break;
    }
  }

  return myOutput;
}

void PIE::PIEAnalysisOutput::pp2Folder(  const std::string path )
{
  using namespace physicalModel;

  std::string pieResults = myUnknowns->prettyPrint();
  tools::interface::exportfile( path + "/" + "pie.dat" , pieResults ) ;

  std::string bestfit = ppThermalSweep();
  tools::interface::exportfile( path + "/" + "thermalSweep.dat" , bestfit ) ;


  for( math::estimation::unknown&parameter : (*myUnknowns)() )
  {
    const physicalModel::labels myLabel = parameter.getLabel();
    const std::string myLabelName = myLabel.getNameString() ;
    filesystem::makeDir( path , myLabelName );

    const std::string updatePath = path + "/" + myLabelName;

    const labels::Name myenumName = myLabel.getName();

    const std::string output = ppSearchPath( myenumName );
    const std::string pathSP =  updatePath + "/" + "searchPath.dat" ;
    tools::interface::exportfile( pathSP , output ) ;

    SearchData mySearchData = retrieveSearchData( myenumName ) ;
    mySearchData.ppThermalSweep( updatePath ) ;

  }

}

std::string PIE::PIEAnalysisOutput::ppThermalSweep( void )
{
  const std::string output = bestFitThermal->prettyPrint( *bestFitCoat ) ;
  return output;
}

std::string PIE::PIEAnalysisOutput::
ppSearchPath( const physicalModel::labels::Name input )
{
  SearchData myData = retrieveSearchData( input ) ;
  const std::string output = myData.pprint() ;

  return output;
}

std::string PIE::PIEAnalysisOutput::
ppEmissionLimits( const physicalModel::labels::Name input )
{
  SearchData myData = retrieveSearchData( input ) ;

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

  ///use the inputs
  unknownParameters = list_in ;
  thermalData = thermalData_in ;
  coreSystem = coreSystem_in ;
  bestfitMethod =  bestfitMethod_in ;

  ///repeat best fit and save the info for output analysis
  bestFit() ;
  ThermalSweepTEMP.bestfit = *thermalData ;
  reassign ( ouputResults.bestFitThermal , *thermalData ) ;
  reassign ( ouputResults.bestFitCoat , coreSystem->TBCsystem.coating ) ;

  parameterIntervalEstimates() ;
  reassign( ouputResults.myUnknowns, *unknownParameters ) ;

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
    ///search space
    (*unknownParameters)( newListVect ) ;

    ///identifiy fixed parameter and update search bound
    const unknown myfixedParameter =  originalListParams[i];
    const enum physicalModel::labels::Name mylabel = myfixedParameter.label();
    const double bestfit = myfixedParameter.bestfit();
    const double lowerbound = myfixedParameter.lowerBound();
    const double upperbound = myfixedParameter.upperBound();

    Gfunc( bestfit , mylabel );
//    std::cerr << "this better be zero = " << Gfunc( bestfit , mylabel )<<"\n";
//    std::cerr << "these are the bounds" << lowerbound <<"\t"<< upperbound<< "\n";
    constexpr double tol  = 1e-12;
    BOOST_ASSERT( std::fabs( Gfunc( bestfit , mylabel ) )  < tol ) ;

    const double min = solveFORx( S1, lowerbound, bestfit , mylabel, "min" ) ;
    ThermalSweepTEMP.lowerbound = *thermalData;

    const double max = solveFORx( S1, bestfit, upperbound , mylabel, "max" ) ;
    ThermalSweepTEMP.upperbound = *thermalData;

    originalListParams[i].bestfitIntervalset( min, max) ;


    ///save search data for later analysis
    dataTempStorage.param = mylabel ;        
    dataTempStorage.thermalSweep = ThermalSweepTEMP;

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

  const std::pair< double, ThermalData > saveThis( val, *thermalData ) ;
  dataTempStorage.allThermalData.push_back( saveThis ) ;

  return thermalData->MSE;
}


}}
