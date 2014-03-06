/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
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
#include <iostream>
#include "sensitivityvaldes2013.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/poptea.hpp"
#include "thermal/emission/phase99.hpp"
#include "math/bisection.hpp"
#include "math/sensitivityAnalysis/estimationInterval.hpp"
#include "thermal/emission/noise.hpp"
#include "math/statistical_tools.hpp"
#include "tools/interface/exportfile.hpp"
#include "tools/interface/xml.h"

namespace investigations
{
namespace sensitivityvaldes2013
{

using namespace thermal::analysis;

void run( const filesystem::directory &dir )
{
  using std::string;
  using namespace physicalModel;
  /// setup output directory
  Poptea poptea = initializePopTeaAndLoadSimuEmission( dir ) ;

  /// Part test
  poptea.bestFit() ;
  std::cout << poptea.ppUnknownParameters() ;


  {
    /// PartA ( pie_analysis )
    const string partA = "/partA_pieAnalysis" ;
    dir.mkdir( partA ) ;
    PIE::PIEAnalysisOutput pieOutput = poptea.PIE() ;

    const string path = dir.abs( partA ) ;
    pieOutput.pp2Folder( path ) ;
    std::cout << poptea.ppUnknownParameters() << "\n" ;
  }

  {
    /// PartB (experimental Optimizer)
    string partB = "/partB_expOptimize" ;
    dir.mkdir( partB ) ;

    for( size_t i =0 ; i < 1 ; ++i )
    {
      poptea.bestFit() ;
      ThermalSweepOptimizer::OptimizerOutput outputData = poptea.optimization() ;
      outputData.pp2Folder( dir.abs( partB ) , std::to_string(i)  ) ;
      std::cout << poptea.ppUnknownParameters() << "\n" ;

      //poptea.resetThermalSweepIni();
    }
  }

  using tools::interface::exportfile;
  const string partC = "/partC_thermalMaps" ;
  {
    /// PartC (thermal Maps)
    dir.mkdir( partC ) ;

    const string path2thermalMap = dir.abs( partC + "/thermalSweepALL.dat" );
    const string thermalSweepMap = poptea.thermalSweepMap() ;
    exportfile( path2thermalMap , thermalSweepMap ) ;
  }

  ///subMaps
  using tools::interface::getTreefromFile;
  using tools::interface::getBranch;
  using boost::property_tree::ptree;
  {
    //// asub
    const string path2asub = dir.abs( "/poptea-asub.xml" ) ;
    const ptree asubTrunk = getTreefromFile( path2asub ) ;
    ptree aBranch = getBranch( "poptea", "optimizationSweep", asubTrunk ) ;
    const methods analysisAsub
        = loadMethodsfromFile( aBranch, *(poptea.unknownParameters),
                               *(poptea.thermalData),
                               poptea.coreSystem->TBCsystem.coating);

    poptea.reloadAnalysis( analysisAsub ) ;
    const string path2asubMap = dir.abs( partC+"/thermalSweep-asub.dat" ) ;
    poptea.bestFit() ;
    const string thermalSweepMapasub = poptea.thermalSweepMap() ;
    exportfile( path2asubMap , thermalSweepMapasub ) ;
  }

  {
    //// gamma
    const string path2gamma = dir.abs( "/poptea-gamma.xml" ) ;
    const ptree gammaTrunk = getTreefromFile( path2gamma );
    const ptree gBranch = getBranch("poptea", "optimizationSweep", gammaTrunk ) ;
    const methods gammaEmphasis = loadMethodsfromFile(
          gBranch, *(poptea.unknownParameters), *(poptea.thermalData),
          poptea.coreSystem->TBCsystem.coating);

    poptea.reloadAnalysis( gammaEmphasis ) ;
    const string path2gammalMap = dir.abs( partC + "/thermalSweep-gamma.dat" ) ;
    poptea.bestFit() ;
    const string thermalSweepMapgam = poptea.thermalSweepMap() ;
    exportfile( path2gammalMap , thermalSweepMapgam ) ;
  }


  return;
}

thermal::analysis::Poptea
initializePopTeaAndLoadSimuEmission( const filesystem::directory &dir )
{
  ///Initialize kernals
  const Kernal popteaCore = loadWorkingDirectoryKernal( dir ) ;
  Poptea poptea = loadWorkingDirectoryPoptea ( dir, popteaCore);

  //Noise in Simulated Emission
  using thermal::emission::ExpNoiseSetting;
  const ExpNoiseSetting myEmissionNoise =ExpNoiseSetting::loadExpNoiseFile(dir);

  ///Output noise to test
  const std::vector<double> emissionNominal =
      thermal::emission::phase99( *(poptea.coreSystem) ,
                                  poptea.thermalData->omegas ) ;

  const std::vector<double> emissionExperimental =
      thermal::emission::addNoise( emissionNominal, poptea.thermalSweep(),
                                   myEmissionNoise ) ;

  poptea.updateExperimentalData( poptea.thermalData->omegas ,
                                 emissionExperimental ) ;

  return poptea;
}

void demo( const filesystem::directory &dir )
{
  thermal::analysis::Poptea poptea = initializePopTeaAndLoadSimuEmission( dir );

  for(size_t i =0 ; i < 100; i++)
    std::cout << "\n";

  poptea.bestFit();

  std::cout << poptea.unknownParameters->prettyPrint();
  std::cout << "Press <ENTER> to continue.\n";
  std::cin.get();
  std::cout << "Please wait...\n";

  poptea.optimization();
}

}}
