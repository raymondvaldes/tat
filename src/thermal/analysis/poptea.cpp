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
#include <functional>
#include <boost/foreach.hpp>

#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/thermalData.hpp"
#include "thermal/emission/phase99.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/lmdiff_poptea_help.hpp"

#include "math/estimation/parameterestimation.hpp"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/lmdiff_helper.hpp"
#include "math/utility.hpp"
#include "math/estimation/constrained.hpp"
#include "math/algorithms/combinations.hpp"

#include "math/bisection.hpp"

namespace thermal {
namespace analysis{  

Poptea::Poptea( const Kernal &coreSystem_ , const ThermalData &thermaldata_,
                const math::estimation::settings &Settings_,
                const math::estimation::unknownList &unknownParameters_)
    : coreSystem( new Kernal(coreSystem_) ),
      thermalData( new ThermalData(thermaldata_)),
      unknownParameters( new math::estimation::unknownList(unknownParameters_)),
      analysis( Settings_, unknownParameters_, thermaldata_ )
{

}

class Poptea
Poptea::loadConfig( const class Kernal &coreSystem_,
                    const boost::property_tree::ptree &pt )
{
  using boost::property_tree::ptree;
  const std::string conjunto = "poptea.";

  const ptree ptchild1 = pt.get_child( conjunto + "sweep");
  const class ThermalData Obj1(
        ThermalData::loadConfigfromXML( ptchild1 ,
                                        coreSystem_.TBCsystem.coating) );

  const ptree ptchild2 = pt.get_child( conjunto + "ParaEstSettings" );
  const class math::estimation::settings
    Obj2( math::estimation::settings::loadConfigfromXML( ptchild2 ) );

  const ptree ptchild3 = pt.get_child( conjunto );
  const class math::estimation::unknownList
    Obj3( math::estimation::unknownList::loadConfigfromXML( ptchild3 ) );


  //Load class object from previous objects
  class Poptea poptea( coreSystem_, Obj1, Obj2, Obj3 ) ;

  return poptea;
}

class Poptea Poptea::loadConfigfromFile( const class filesystem::directory &dir )
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
    std::cout << "file " << dir.abs( filename1 ) << " not found! See --help\n";
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
    std::cout << "file " << dir.abs( filename ) << " not found! See --help\n";
    exit(-2);
  }

  ///return this object
  return Poptea::loadConfig( popteaCore, pt1 );
}


//void Poptea::updatelthermal( const double lmin, const double lmax )
//{
//  thermalData.thermalSetup( lmin, lmax, coreSystem.TBCsystem.coating ) ;
//}

void Poptea::updateExperimentalData( const std::vector<double> &omegas,
                                     const std::vector<double> &input )
{
  assert( input.size() == omegas.size());
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
  double output = 0;
  output =  analysis.bestFit( unknownParameters, thermalData, coreSystem);

  return output;
}

void Poptea::PIE ( void )
{
  analysis.parameterIntervalEstimates( unknownParameters , thermalData,
                                       coreSystem ) ;
}

void Poptea::parameterIntervalEstimates( void )
{
  /// Precheck experimental data is loaded and there is a bestfit.
  if(!loadedExperimental) { return; }
  bestFit();

  std::cout << "iterate through parameters now:---\n\n";
  std::cout << "parameter estimates intervals:\n";
  std::cout << "------------------------------\n\n";
  std::cout << "min\tbestfit\tmax\n";


  PIE();

  std::cout << "iterate through parameters now:---\n\n";
  std::cout << "parameter estimates intervals:\n";
  std::cout << "------------------------------\n\n";
  std::cout << "min\tbestfit\tmax\n";

  for(auto& val : (*unknownParameters)() )
  {
    std::cout << val.bestfitInterval.lower << "\t"   <<  val.bestfit()
              << "\t"   << val.bestfitInterval.upper << "\n";
  }
}

void Poptea::optimization(void)
{
  if(!loadedExperimental) { return; }
  bestFit();

  analysis.optimization( unknownParameters , thermalData, coreSystem);


}


class Poptea loadWorkingDirectoryPoptea( const class filesystem::directory dir,
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
    std::cout << "file " << dir.abs( filename ) << " not found! See --help\n";
    exit(-2);
  }

  return Poptea::loadConfig( popteaCore, pt );
}

//void Poptea::updateUnknownParameters(
//    const std::vector< class math::estimation::unknown > &unknownList_ )
//{
//  std::vector<class math::estimation::unknown> updated(unknownList_);
//  unknownParameters( updated );

//  const size_t Default = thermalData.experimentalEmission.size();
//}


}}
