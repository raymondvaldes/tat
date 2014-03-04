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
#include <boost/foreach.hpp>
#include "thermal/analysis/poptea.hpp"
#include "tools/interface/xml.h"

namespace thermal {
namespace analysis{  

Poptea::Poptea( const Kernal &coreSystem_ , const ThermalData &thermaldata_,
                const math::estimation::unknownList &unknownParameters_,
                const methods analysis_in )
    : analysis( analysis_in )
{
  reassign( coreSystem, coreSystem_);
  reassign( thermalData, thermaldata_);
  reassign( unknownParameters, unknownParameters_);
}

class Poptea
Poptea::loadConfig( const Kernal &coreSystem_,
                    const boost::property_tree::ptree &pt )
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

class Poptea Poptea::loadConfigfromFile( const class filesystem::directory &dir)
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
                                     const std::vector<double> &input )
{
  BOOST_ASSERT( input.size() == omegas.size());
  loadedExperimental = true;

  thermalData->updateExperimental( input );
}

Poptea::~Poptea(void){}

std::vector<double> Poptea::thermalSweep(void) const
{
  return thermalData->get_lthermalSweep( coreSystem->TBCsystem.coating ) ;
}


double Poptea::bestFit( void )
{
  runbestfit = true;

  const double output = analysis.bestFit( unknownParameters, thermalData,
                                          coreSystem ) ;
  unknownParameters->prettyPrint();

  return  output;
}

thermal::analysis::PIE::PIEAnalysisOutput Poptea::PIE( void )
{
  return analysis.parameterIntervalEstimates( unknownParameters , thermalData,
                                              coreSystem ) ;
}

ThermalSweepOptimizer::OptimizerOutput Poptea::optimization(void)
{
  BOOST_ASSERT_MSG( loadedExperimental , "must load experimental data!" );

  return analysis.optimization( unknownParameters , thermalData, coreSystem ) ;
}

std::string Poptea::thermalSweepMap( void )
{
  BOOST_ASSERT_MSG( loadedExperimental , "must load experimental data!" ) ;
  return analysis.montecarloMap( unknownParameters , thermalData, coreSystem ) ;
}

void Poptea::resetThermalSweepIni( void )
{
  analysis.resetThermalSweepIni();
}



std::string Poptea::ppUnknownParameters ( void )
{
  return unknownParameters->prettyPrint();
}

std::string Poptea::ppThermalData( void )
{
  return thermalData->prettyPrint( coreSystem->TBCsystem.coating ) ;
}

void Poptea::reloadAnalysis( const methods &analysis_in )
{
  analysis = analysis_in;
}


Poptea loadWorkingDirectoryPoptea( const class filesystem::directory dir,
                                   const class Kernal &popteaCore )
{
  const std::string filename = "poptea.xml";
  boost::property_tree::ptree
      pt = tools::interface::getTreefromFile( dir.abs( filename ) ) ;


  return Poptea::loadConfig( popteaCore, pt );
}

}}
