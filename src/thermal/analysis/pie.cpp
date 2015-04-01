/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <utility>
#include "thermal/analysis/pie.hpp"
#include "math/algorithms/combinations.hpp"
#include "tools/interface/exportfile.hpp"
#include "tools/interface/filesystem.hpp"

//#include "math/estimation/utils.hpp"

namespace thermal{
namespace analysis{

PIE::PIE( void ) noexcept
{ }

PIE::~PIE() noexcept {} 

std::string PIE::PIEAnalysisOutput::SearchData::pprint( void ) noexcept
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

void PIE::PIEAnalysisOutput::ThermalSweep::prettyPrint(const std::string folder) noexcept
{
  typedef const std::string filePath;
  typedef const std::string outputString;

  filePath newFolder = "thermalSweep" ;
  filesystem::makeDir( folder , newFolder ) ;
  filePath updatedPath = folder + "/" +newFolder ;

  outputString output1 = bestfit.prettyPrint();
  outputString output2 = upperbound.prettyPrint();
  outputString output3 = lowerbound.prettyPrint();

  filePath path1 =  updatedPath + "/" + "bestfit.dat" ;
  filePath path2 =  updatedPath + "/" + "upperbound.dat" ;
  filePath path3 =  updatedPath + "/" + "lowerbound.dat" ;

  tools::interface::exportfile( path1 , output1 ) ;
  tools::interface::exportfile( path2 , output2 ) ;
  tools::interface::exportfile( path3 , output3 ) ;
}


void PIE::PIEAnalysisOutput::SearchData::
  ppThermalSweep ( const std::string folder) noexcept
{
  thermalSweep.prettyPrint( folder );
}


double PIE::bestFit() noexcept
{
  bestfitMethod->solve( unknownParameters, thermalData, coreSystem ) ;
  return thermalData->MSE;
}


PIE::PIEAnalysisOutput::SearchData PIE::PIEAnalysisOutput::
retrieveSearchData( const thermal::model::labels::Name input ) noexcept
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

void PIE::PIEAnalysisOutput::pp2Folder(  const std::string path ) noexcept
{
  std::string pieResults = myUnknowns->prettyPrint();
  tools::interface::exportfile( path + "/" + "pie.dat" , pieResults ) ;

  std::string bestfit = ppThermalSweep();
  tools::interface::exportfile( path + "/" + "thermalSweep.dat" , bestfit ) ;


  for( math::estimation::unknown&parameter : (*myUnknowns)() )
  {
    const thermal::model::labels myLabel = parameter.getLabel();
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

std::string PIE::PIEAnalysisOutput::ppThermalSweep( void ) noexcept
{
  const std::string output = bestFitThermal->prettyPrint( *trueCoat ) ;
  return output;
}

std::string PIE::PIEAnalysisOutput::
ppSearchPath( const thermal::model::labels::Name input ) noexcept
{
  SearchData myData = retrieveSearchData( input ) ;
  const std::string output = myData.pprint() ;

  return output;
}

std::string PIE::PIEAnalysisOutput::
ppEmissionLimits( const thermal::model::labels::Name input ) noexcept
{
  SearchData myData = retrieveSearchData( input ) ;

  const std::string output = myData.pprint() ;
  return output;
}



void PIE::PIEAnalysisOutput::clear( void ) noexcept
{
  searchPath.clear();
}

PIE::PIEAnalysisOutput 
PIE::solve( const std::shared_ptr<math::estimation::unknownList> &list_in,
            const std::shared_ptr<ThermalData> &thermalData_in,
            const std::shared_ptr<Kernal> &coreSystem_in, 
            const std::shared_ptr<LMA> bestfitMethod_in ) noexcept
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
  reassign ( ouputResults.trueCoat , coreSystem->TBCsystem.truecoating ) ;


  parameterIntervalEstimates() ;
  reassign( ouputResults.myUnknowns, *unknownParameters ) ;

  return ouputResults;
}

void PIE::parameterIntervalEstimates( void ) noexcept
{
  /// Save experimental data, quality-of-fit, unknownParameter List
  using math::estimation::unknown;
  using std::vector;
  using std::abs;
  using math::algorithms::combos_minusOne;


  vector< unknown > originalListParams( ( *unknownParameters )() ) ;
  saveExperimental( *thermalData ) ;
  const double S1 = thermalData->MSE ;

  /// Update initial guess using bestfits
  for( auto& param : originalListParams )
    param.Initialset( param.bestfit() );

  /// Predicted emission as the new experimental
  const vector<double> TEMPExperimental = thermalData->predictedEmission ;
  updateExperimentalData( TEMPExperimental, *thermalData ) ;

  /// Create list of parameters that must be refitted
  const vector< vector<  unknown > >
      unknownParaLists = combos_minusOne( originalListParams );

  vector< enum thermal::model::labels::Name  > parametersToBeManipulated;
  for ( auto const& unknown : originalListParams )
    parametersToBeManipulated.push_back( unknown.label() );

  /// update list of parameters using unknownIterations
  size_t i = 0;
  for( auto& newListVect : unknownParaLists )
  {
    ///search space
    (*unknownParameters)( newListVect ) ;

    ///identifiy fixed parameter and update search bound
    const unknown myfixedParameter =  originalListParams[i] ;
    const enum thermal::model::labels::Name mylabel = myfixedParameter.label() ;
    const double bestfit = myfixedParameter.bestfit() ;
    const double lowerbound = myfixedParameter.lowerBound() ;
    const double upperbound = myfixedParameter.upperBound() ;

    //std::cerr << "this better be zero = " << Gfunc( bestfit , mylabel )<<"\n";
    //std::cerr << "these are the bounds" << lowerbound <<"\t"<< upperbound<< "\n";
    constexpr double tol  = 1e-8;
    const double gcheck = Gfunc( bestfit , mylabel );
    BOOST_ASSERT( abs( gcheck )  < tol ) ;

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
  
  //Reset originalListParams with the preserved initials
  for( size_t j = 0 ; i < originalListParams.size() ; ++i )
  {
    const double initial = (*unknownParameters).vectorUnknowns[j].initialVal();
    originalListParams[j].Initialset( initial ) ;
  }

  ///Update list of parameters with updated list
  (*unknownParameters)( originalListParams );

  reloadExperimental();
  thermalData->MSE = S1;
}

double PIE::solveFORx( const double target , const double min, const double max,
                       const enum thermal::model::labels::Name mylabel,
                       const std::string &bound ) noexcept
{
  using std::function;
  using std::bind;
  using std::placeholders::_1;
  
  const function<double(double)>
    myFuncReduced = bind( &PIE::Gfunc, this , _1, mylabel ) ;
  const math::solve ojb( myFuncReduced, target, min, max ) ;
  double soln = ojb.returnSoln();

  if( !ojb.pass )
  {
    if( bound == "min" ) soln = min;
    if( bound == "max" ) soln = max;
  }

  return soln;
}

double PIE::Gfunc( const double val ,
                   const enum thermal::model::labels::Name &mylabel ) noexcept
{
  using std::pair;

  coreSystem->TBCsystem.updateVal( mylabel , val ) ;
  coreSystem->TBCsystem.updateCoat() ;

  const double error = bestFit() ;

  const pair< double, ThermalData > saveThis( val, *thermalData ) ;
  dataTempStorage.allThermalData.push_back( saveThis ) ;

  return error;
}

void PIE::saveExperimental( const ThermalData& thermalData_in ) noexcept
{
  SAVEExperimental = thermalData_in.experimentalEmission;
  SAVEpredictions = thermalData_in.predictedEmission;
  SAVEomega = thermalData_in.omegas;
}

void PIE::reloadExperimental( void ) noexcept
{
  thermalData->experimentalEmission = SAVEExperimental;
  thermalData->predictedEmission = SAVEpredictions;
  thermalData->omegas = SAVEomega;
}

void PIE::updateExperimentalData( const std::vector<double> &input,
                                  ThermalData &thermalData_in ) noexcept
{
  thermalData_in.updateExperimental( input );
}





}}
