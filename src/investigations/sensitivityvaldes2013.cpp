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
#include "algorithms/statistical_tools.hpp"

namespace investigations
{
  namespace sensitivityvaldes2013{

class thermal::analysis::Kernal
    loadWorkingDirectory(const class filesystem::directory dir)
{
  const std::string filename = "kernal.xml";
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

  return thermal::analysis::Kernal::loadConfig( pt , dir);
}

class thermal::analysis::Poptea
    loadWorkingDirectoryPoptea( const class filesystem::directory dir,
                                const class thermal::analysis::Kernal popteaCore)
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

  return thermal::analysis::Poptea::loadConfig( popteaCore, pt );
}


void run(const class filesystem::directory dir)
{
  ///Initialize kernals
  class thermal::analysis::Kernal popteaCore = loadWorkingDirectory(dir);
  class thermal::analysis::Poptea
      poptea = loadWorkingDirectoryPoptea ( dir, popteaCore );

  /// STEP 0
  //Noise in Simulated Emission
  constexpr double a =  .01;   // max % error (%*pi/2) (try .025)
  constexpr double b = 2.95;   // stretching parameter  (try 2.95) (1->pi)
  constexpr bool d1 = true;    //positive  (try false)
  constexpr bool d2 = true;    //monotonic (try true)
  constexpr int s1 = 0;        //-1(left bias) 0(symmetric) +1(right bias)
  constexpr double noiseRandom = 0.005*0; // normal noise % of pi/2

  const class thermal::emission::ExpNoiseSetting
      myEmissionNoise( a, b, d1, d2, s1, noiseRandom );

  ///Output noise to test
  std::vector<double>
      emissionNominal =  thermal::emission::phase99( poptea.coreSystem ,
                                                     poptea.l_thermal);

  std::vector<double> emissionExperimental =
        thermal::emission::addNoise( emissionNominal,
                                     poptea.l_thermal,
                                     myEmissionNoise ) ;
//poptea.coreSystem.LMA.LMA_workspace.emissionExperimental//

  poptea.loadExperimentalData( emissionExperimental );

//  ///Output noise to test
//  for( size_t i = 0 ; i < popteaCore.expSetup.laser.l_thermal.size() ; ++i)
//  {
//    std::cout <<  popteaCore.expSetup.laser.l_thermal[i] << "\t"
//              <<  popteaCore.LMA.LMA_workspace.emissionNominal[i] << "\t"
//              <<  popteaCore.LMA.LMA_workspace.emissionExperimental[i] << "\n" ;
//  }

  /// STEP 1
//  poptea.setParametertoFit( poptea.coreSystem.LMA.unknownParameters );
//  poptea.saveListunknowns();
//  poptea.bestFit( poptea.coreSystem );




//  for( size_t i = 0 ; i < popteaCore.LMA.xpredicted.size() ;  i++)
//  {
//    std::cout << popteaCore.LMA.xpredicted[i] << "\n";
//  }

//  /// STEP 2
////  thermal::emission::phase99( popteaCore, popteaCore.LMA.LMA_workspace.predicted );

//  poptea.coreSystem.LMA.LMA_workspace.predicted =
//  thermal::emission::phase99( poptea.coreSystem );

//  poptea.coreSystem.LMA.LMA_workspace.MSE =
//      MSE( poptea.coreSystem.expSetup.laser.L_end,
//           poptea.coreSystem.LMA.LMA_workspace.emissionExperimental,
//           poptea.coreSystem.LMA.LMA_workspace.predicted ) ;

//  std::cout << poptea.coreSystem.LMA.LMA_workspace.MSE << "\n";

//  /// STEP 3

//  /// STEP 4
//  class math::estimation::unknown
//      first(poptea.coreSystem.LMA.unknownParameters.vectorUnknowns[0]);

//  class math::sensitivityAnalysis::step4 Step4;
//  std::cout << "this is the output\n\n" << Step4.solve() << "\n";

//  std::cout << "**********************************************\n" ;
//  std::cout << "**********************************************\n" ;
//  std::cout << "**********************************************\n" ;
//  std::cout << "**********************************************\n" ;
//  std::cout << "**********************************************\n" ;





//  void setThermalRange(const double lmin, const double lmax);
//  void setParametertoFit( class math::estimation::unknownList parameters );
//  void setParametertoHoldX(enum physicalModel::labels::Name currentParameterX_);


//  double Gfunc( const double x );
// ///Gfunc must work by updating kernal with unknown parameters
// ///updating experimental with predicted values;

//  std::pair< double, double >
//  Gsolve( enum physicalModel::labels::Name currentParameterX_ );

//  void saveBestFitParameters( void );
//  void setG1(void);



  return;
}





}
}

