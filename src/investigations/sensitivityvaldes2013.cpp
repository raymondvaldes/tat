/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <vector>
#include <iostream>
#include "sensitivityvaldes2013.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/poptea.hpp"
#include "thermal/emission/phase99.hpp"
#include "math/bisection.hpp"

#include "thermal/emission/noise.hpp"

#include "tools/interface/exportfile.hpp"
#include "tools/interface/xml.h"
#include "thermal/analysis/poptea_initialize.h"

namespace investigations
{
namespace sensitivityvaldes2013
{

using namespace thermal::analysis;

void run( const filesystem::directory &dir ) noexcept
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



void demo( const filesystem::directory &dir ) noexcept
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
