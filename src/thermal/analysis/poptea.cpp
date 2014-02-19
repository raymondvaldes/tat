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

namespace thermal {
namespace analysis{  

Poptea::Poptea( const Kernal &coreSystem_ , const ThermalData &thermaldata_,
                const math::estimation::settings &Settings_,
                const math::estimation::unknownList &unknownParameters_,
                const math::estimation::unknownList &thermalSweepSearch ,
                const std::vector<physicalModel::labels> sweepOptimizationGoal)
    : analysis( Settings_, unknownParameters_, thermaldata_, thermalSweepSearch,
                sweepOptimizationGoal, coreSystem_.TBCsystem.coating )
{
  reassign( coreSystem, coreSystem_);
  reassign( thermalData, thermaldata_);
  reassign( unknownParameters, unknownParameters_);
}

class Poptea
Poptea::loadConfig( const Kernal &coreSystem_,
                    const boost::property_tree::ptree &pt )
{
  using boost::property_tree::ptree;
  const std::string conjunto = "poptea." ;

  /// Initiate poptea constructor objects
  const ptree ptchild1 = pt.get_child( conjunto + "sweep");
  const ThermalData thermData(
        ThermalData::loadConfigfromXML( ptchild1 ,
                                        coreSystem_.TBCsystem.coating) );

  const ptree ptchild2 = pt.get_child( conjunto + "ParaEstSettings" );
  const math::estimation::settings
    estSettings( math::estimation::settings::loadConfigfromXML( ptchild2 ) );

  const ptree ptchild3 = pt.get_child( conjunto ) ;
  const math::estimation::unknownList
    parameterEstimation(
        math::estimation::unknownList::loadConfigfromXML( ptchild3 ) );


  const ptree ptchild4 = pt.get_child( conjunto + "optimizationSweep") ;
  const math::estimation::unknownList
    thermalSweep( math::estimation::unknownList::loadConfigfromXML( ptchild4 ));

  std::vector< physicalModel::labels > sweepOptimizationGoal;
  BOOST_FOREACH( const ptree::value_type &v,
                 ptchild4.get_child( "parameters" ) )
  {
    //retrieve subtree
    const ptree& child = v.second;

    //access members of subtree
    physicalModel::labels labelmaker;
    const std::string nameLabel = child.get< std::string >( "label" );
    enum physicalModel::labels::Name mylabel;
    try
    {
      mylabel = labelmaker.nameMap.right.at(nameLabel);
    }
    catch( std::exception& e )
    {
      std::cerr << "Error with label in config.xml config\n";
      exit(1);
    }
    const physicalModel::labels output(mylabel);
    sweepOptimizationGoal.push_back( output );
  }

  //Load class object from previous objects
  const Poptea poptea( coreSystem_, thermData, estSettings, parameterEstimation,
                       thermalSweep, sweepOptimizationGoal ) ;

  return poptea;
}

class Poptea Poptea::loadConfigfromFile( const class filesystem::directory &dir)
{
  ///Initiate poptea kernal
  const std::string filename1 = "kernal.xml";
  boost::property_tree::ptree pt;
  try
  {
    boost::property_tree::read_xml( dir.abs( filename1 ), pt );
  }
  catch (std::exception& e)
  {
    std::cerr << "file " << dir.abs( filename1 ) << " not found! See --help\n";
    exit(-2);
  }
  const class Kernal popteaCore = Kernal::loadConfig( pt , dir );

  ///bring full poptea object online
  const std::string filename = "poptea.xml";
  boost::property_tree::ptree pt1;
  try
  {
    boost::property_tree::read_xml( dir.abs( filename ), pt1 );
  }
  catch (std::exception& e)
  {
    std::cerr << "file " << dir.abs( filename ) << " not found! See --help\n";
    exit(-2);
  }

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
  return thermalData->get_lthermalSweep( coreSystem->TBCsystem.coating );
}


double Poptea::bestFit( void )
{
  runbestfit = true;

  double output = analysis.bestFit( unknownParameters, thermalData, coreSystem );
  unknownParameters->prettyPrint();

  return  output;
}

thermal::analysis::PIE::PIEAnalysisOutput Poptea::PIE( void )
{
  return analysis.parameterIntervalEstimates( unknownParameters , thermalData,
                                              coreSystem ) ;
}

void Poptea::optimization(void)
{
  if(!loadedExperimental) { return; }

  analysis.optimization( unknownParameters , thermalData, coreSystem);
}

std::string Poptea::ppUnknownParameters ( void )
{
  return unknownParameters->prettyPrint();
}

std::string Poptea::ppThermalData( void )
{
  return thermalData->prettyPrint( coreSystem->TBCsystem.coating ) ;
}


Poptea loadWorkingDirectoryPoptea( const class filesystem::directory dir,
                                         const class Kernal &popteaCore)
{
  const std::string filename = "poptea.xml";
  boost::property_tree::ptree pt;
  try
  {
    boost::property_tree::read_xml( dir.abs( filename ), pt);
  }
  catch (std::exception& e)
  {
    std::cerr << "file " << dir.abs( filename ) << " not found! See --help\n";
    exit(-2);
  }

  return Poptea::loadConfig( popteaCore, pt );
}

}}
