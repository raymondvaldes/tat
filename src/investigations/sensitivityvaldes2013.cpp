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

void run( const filesystem::directory dir )
{
  /// setup output directory
  Poptea poptea = initializePopTeaAndLoadSimuEmission( dir ) ;

  /// Part test
  poptea.bestFit() ;
  std::cout << poptea.ppUnknownParameters() ;

  /// PartA ( pie_analysis )
  const std::string partA = "/partA_pieAnalysis" ;
  dir.mkdir( partA ) ;

  PIE::PIEAnalysisOutput pieOutput = poptea.PIE() ;
  const std::string path = dir.abs( partA ) ;
  pieOutput.pp2Folder( path ) ;
  std::cout << poptea.ppUnknownParameters() << "\n" ;

  /// PartB (experimental Optimizer)
  const std::string partB = "/partB_expOptimize" ;
  dir.mkdir( partB ) ;
  ThermalSweepOptimizer::OptimizerOutput outputData = poptea.optimization() ;
  const std::string pathB = dir.abs( partB ) ;
  outputData.pp2Folder( pathB ) ;

  /// PartC (thermal Maps)
  const std::string partC = "/partC_thermalMaps" ;
  dir.mkdir( partC ) ;


  std::string thermalSweepMap = poptea.thermalSweepMap( 10 ) ;
//  std::string path2thermalMap = pathB + "/" + "thermalSweepMap.dat" ;
//  tools::interface::exportfile( path2thermalMap , thermalSweepMap ) ;

  return;
}

thermal::analysis::Poptea
initializePopTeaAndLoadSimuEmission( const filesystem::directory dir )
{
  ///Initialize kernals
  const thermal::analysis::Kernal
      popteaCore = thermal::analysis::loadWorkingDirectoryKernal(dir);
  thermal::analysis::Poptea
      poptea = thermal::analysis::loadWorkingDirectoryPoptea ( dir, popteaCore);

  //Noise in Simulated Emission
  const thermal::emission::ExpNoiseSetting myEmissionNoise =
  thermal::emission::ExpNoiseSetting::loadExpNoiseFile( dir );

  ///Output noise to test
  const std::vector<double> emissionNominal =
      thermal::emission::phase99( *(poptea.coreSystem) ,
                                  poptea.thermalData->omegas ) ;

  const std::vector<double> emissionExperimental = thermal::emission::
      addNoise( emissionNominal, poptea.thermalSweep(), myEmissionNoise ) ;

  poptea.updateExperimentalData( poptea.thermalData->omegas ,
                                 emissionExperimental ) ;

  return poptea;
}

void demo( const filesystem::directory dir )
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
