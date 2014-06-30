/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  	        	|
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
#include "thermal/analysis/poptea_initialize.h"

namespace investigations
{
namespace sensitivityvaldes2013
{

using namespace thermal::analysis;

void run( const filesystem::directory &dir )
{
  using std::string;
  using std::to_string;
  using std::cout;
  
  /// setup output directory
  Poptea poptea = initializePopTeaAndLoadSimuEmission( dir ) ;


  /// Part test
  poptea.bestFit() ;
  cout << poptea.ppUnknownParameters() ;

  {
    /// PartA ( pie_analysis )
    const string partA = "/partA_pieAnalysis" ;
    dir.mkdir( partA ) ;
    PIE::PIEAnalysisOutput pieOutput = poptea.PIE() ;

    const string path = dir.abs( partA ) ;
    pieOutput.pp2Folder( path ) ;
    cout << poptea.ppUnknownParameters() << "\n" ;
  }

  {
    /// PartB (experimental Optimizer)
    string partB = "partB_expOptimize" ;
    dir.mkdir( partB ) ;
    poptea.bestFit() ;
    ThermalSweepOptimizer::OptimizerOutput outputData = poptea.optimization() ;
    outputData.pp2Folder( dir.abs( partB ) , to_string(0)  ) ;
    cout << poptea.ppUnknownParameters() << "\n" ;
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
  
return;
}



void demo( const filesystem::directory &dir )
{
  using thermal::analysis::initializePopTeaAndLoadSimuEmission;
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
