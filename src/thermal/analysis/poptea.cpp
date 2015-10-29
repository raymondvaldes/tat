/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include "thermal/analysis/poptea.hpp"
#include "tools/interface/xml.h"

#include "tools/interface/import/columnData.h"
#include "units/container/string_to_quantity.h"

namespace thermal {
namespace analysis{  

Poptea::Poptea( const Kernal &coreSystem_ , const ThermalData &thermaldata_,
                const math::estimation::unknownList &unknownParameters_,
                const methods analysis_in ) noexcept
    : analysis( analysis_in )
{
  reassign( coreSystem, coreSystem_);
  reassign( thermalData, thermaldata_);
  reassign( unknownParameters, unknownParameters_);
}

auto Poptea::loadTBDfile( filesystem::directory const & dir,
                          std::string const & inputFileName )
  -> std::vector< units::quantity<units::si::electric_potential >>
{
  using units::quantity;
  using units::si::electric_potential;
  using units::si::millivolts;
  
  using tools::interface::import::columnData;
  using units::container::string_to_quantity;
  

  auto const fileName_string = dir.abs( inputFileName );
  columnData const myData{ fileName_string } ;
  
  auto const strings = myData.getColumn( 3 ) ;

  auto const myEmissionVector =
  string_to_quantity< electric_potential >( strings, millivolts  ) ;

  return myEmissionVector;
}

Poptea
Poptea::loadConfig( const Kernal &coreSystem_,
                    const boost::property_tree::ptree &pt ) noexcept
{
  using math::estimation::unknownList;
  using boost::property_tree::ptree;
  const std::string conjunto = "poptea." ;

  /// Initiate poptea constructor objects
  const ptree ptchild1 = pt.get_child( conjunto + "sweep") ;
  const ThermalData thermData(
        ThermalData::loadConfigfromXML( ptchild1 ,
                                        coreSystem_.TBCsystem.coating) ) ;

  const ptree ptchild3 = pt.get_child( conjunto ) ;
  const unknownList
    parameterEstimation( unknownList::loadConfigfromXML( ptchild3 ) ) ;


  const ptree ptchild4 = pt.get_child( conjunto + "optimizationSweep" ) ;

  const methods analysis_obj =
  loadMethodsfromFile( ptchild4, parameterEstimation, thermData,
                       coreSystem_.TBCsystem.coating ) ;

  //Load class object from previous objects
  const Poptea poptea( coreSystem_, thermData, parameterEstimation,
                       analysis_obj ) ;
  return poptea ;
}

Poptea Poptea::loadConfigfromFile( const filesystem::directory &dir) noexcept
{
  using boost::property_tree::ptree;

  ///Initiate poptea kernal
  const std::string filename1 = "kernal.xml";
  ptree pt = tools::interface::getTreefromFile( dir.abs( filename1 ) ) ;
  const class Kernal popteaCore = Kernal::loadConfig( pt , dir );

  ///bring full poptea object online
  const std::string filename = "poptea.xml";
  ptree pt1 = tools::interface::getTreefromFile( dir.abs( filename ) ) ;

  ///return this object
  return Poptea::loadConfig( popteaCore, pt1 );
}


void Poptea::updateExperimentalData( const std::vector<double> &omegas,
                                     const std::vector<double> &input ) noexcept
{
  BOOST_ASSERT( input.size() == omegas.size());
  loadedExperimental = true;

  thermalData->updateExperimental( input );
}

void Poptea::updateModelData( const std::vector<double> &omegas,
                              const std::vector<double> &input ) noexcept
{
  BOOST_ASSERT( omegas == thermalData->omegas ) ;
  BOOST_ASSERT( input.size() == thermalData->size() ) ;
  thermalData->predictedEmission = input ;
}

Poptea::~Poptea(void) noexcept {}

std::vector<double> Poptea::thermalSweep(void) const noexcept
{
  return thermalData->get_lthermalSweep( coreSystem->TBCsystem.coating ) ;
}


double Poptea::bestFit( void ) noexcept
{
  runbestfit = true;
  const double output = analysis.bestFit( unknownParameters, thermalData,
                                          coreSystem ) ;
  unknownParameters->prettyPrint();

  return  output;
}

thermal::analysis::PIE::PIEAnalysisOutput Poptea::PIE( void ) noexcept
{
  return analysis.parameterIntervalEstimates( unknownParameters , thermalData,
                                              coreSystem ) ;
}

ThermalSweepOptimizer::OptimizerOutput Poptea::optimization(void) noexcept
{
  BOOST_ASSERT_MSG( loadedExperimental , "must load experimental data!" );

  return analysis.optimization( unknownParameters , thermalData, coreSystem ) ;
}

std::string Poptea::thermalSweepMap( void ) noexcept
{
  BOOST_ASSERT_MSG( loadedExperimental , "must load experimental data!" ) ;
  return analysis.contourMapping() ;
}



std::string Poptea::ppUnknownParameters ( void ) noexcept
{
  return unknownParameters->prettyPrint();
}

std::string Poptea::ppThermalData( void ) noexcept
{
  return thermalData->prettyPrint( coreSystem->TBCsystem.coating ) ;
}

void Poptea::reloadAnalysis( const methods &analysis_in ) noexcept
{
  analysis = analysis_in;
}
  
void Poptea::reloadThermalModel( const thermal::define::construct &in_ ) noexcept
{
  coreSystem->thermalsys.reloadThermalConstruct( in_ );
}

void Poptea::taylor_uncertainty( void ) noexcept
{
  analysis.GUM_uncertainty( unknownParameters , thermalData, coreSystem ) ;
}

Poptea loadWorkingDirectoryPoptea( const filesystem::directory &dir,
                                   const Kernal &popteaCore ) noexcept
{
  const std::string filename = "poptea.xml";
  boost::property_tree::ptree
      pt = tools::interface::getTreefromFile( dir.abs( filename ) ) ;


  return Poptea::loadConfig( popteaCore, pt );
}



}}
