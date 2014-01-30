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

#include <functional>
#include "math/bisection.hpp"

namespace thermal {
namespace analysis{  

Poptea::Poptea( const class Kernal &coreSystem_ ,
                const class ThermalData &thermaldata_,
                const class math::estimation::settings &Settings_,
                const class math::estimation::unknownList &unknownParameters_)
  : coreSystem( coreSystem_ ), thermalData( thermaldata_ ),
    LMA( Settings_, unknownParameters_, thermalData.omegas.size(), thermalData )
{}

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

void Poptea::updatelthermal( const double lmin, const double lmax,
                             const double lminperDecade)
{
  const size_t Lend =
  thermalData.thermalSetup( lmin, lmax, lminperDecade,
                            coreSystem.TBCsystem.coating ) ;

  LMA.updateWorkSpace( Lend, LMA.unknownParameters.size() );
}

void Poptea::updateExperimentalData( const std::vector<double> &omegas,
                                     const std::vector<double> &input)
{
  assert( input.size() == omegas.size());
  loadedExperimental = true;

  thermalData.updateOmegas( omegas , coreSystem.TBCsystem.coating );
  thermalData.updateExperimental( input );
  LMA.updateWorkSpace( input.size() , LMA.unknownParameters.size()  );
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

Poptea::~Poptea(void){}


double Poptea::bestFit( void )
{
  runbestfit = true;

  int nfev;
  int info;

  thermalData = LMA.paramter_estimation( &info, &nfev, coreSystem, thermalData);
  coreSystem.updatefromBestFit( LMA.unknownParameters() );

  return thermalData.MSE;
}

void Poptea::parameterIntervalEstimates( void )
{
  /// Precheck experimental data is loaded and there is a bestfit.
  if(!loadedExperimental) { return; }
  if(!runbestfit) { bestFit(); }

  /// Save experimental data, quality-of-fit, unknownParameter List
  using math::estimation::unknown;
  std::vector< unknown > originalListParams = LMA.unknownParameters();
  const std::vector<double> SAVEExperimental = thermalData.experimentalEmission;
  const double S1 = thermalData.MSE;

  /// Update initial guess using bestfits
  for( auto& param : originalListParams)
    { param.Initialset( param.bestfit() ); }

  /// Predicted emission as the new experimental
  const std::vector<double> TEMPemissionExperimental = thermalData.predictedEmission;
  updateExperimentalData( thermalData.omegas , TEMPemissionExperimental );

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
    LMA.unknownParameters( updatedListParameters );

    ///identifiy fixed parameter and update search bound
    const class unknown myfixedParameter =  originalListParams[i];
    const enum physicalModel::labels::Name
        mylabel = myfixedParameter.label();
    const double bestfit = myfixedParameter.bestfit();
    const double lowerbound = myfixedParameter.lowerBound();
    const double upperbound = myfixedParameter.upperBound();

    ///search space
    const double min = solve( S1, lowerbound, bestfit , mylabel, "min" );
    const double max = solve( S1, bestfit, upperbound , mylabel, "max" );

    originalListParams[i++].bestfitIntervalset( min, max);
  }

  ///Update list of parameters with updated list
  LMA.unknownParameters( originalListParams ) ;
  updateExperimentalData( thermalData.omegas , SAVEExperimental );
  thermalData.MSE = S1;
}

double Poptea::Gfunc( const double val ,
                      const enum physicalModel::labels::Name &mylabel )
{
  coreSystem.TBCsystem.updateVal( mylabel , val );
  coreSystem.TBCsystem.updateCoat();
  bestFit();

  return thermalData.MSE;
}

double Poptea::solve( const double target , const double min, const double max,
                      const enum physicalModel::labels::Name &mylabel,
                      const std::string &bound )
{
  using std::placeholders::_1;
  const std::function<double(double)>
      myFuncReduced = std::bind( &Poptea::Gfunc, this , _1 , mylabel);

  const math::solve ojb( myFuncReduced, target, min, max ) ;
  double soln = ojb.returnSoln();

  if(!ojb.pass)
  {
    if(bound == "min") soln = min;
    if(bound == "max") soln = max;
  }

  return soln;
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




}}
