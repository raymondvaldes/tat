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
#include "sensitivityvaldes2013.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/emission/phase99.hpp"
#include "math/bisection.hpp"
#include "math/sensitivityAnalysis/estimationInterval.hpp"

namespace investigations
{
  namespace sensitivityvaldes2013{

class thermal::analysis::Kernal
    loadWorkingDirectory(const class filesystem::directory dir)
{
  const std::string filename = "config.xml";
  return thermal::analysis::Kernal::loadConfig( dir.abs( filename ), dir);
}

void run(const class filesystem::directory dir)
{
  class thermal::analysis::Kernal popteaCore = loadWorkingDirectory(dir);
  thermal::emission::phase99( popteaCore, popteaCore.LMA.LMA_workspace.emissionNominal);

  /// STEP 0
  /*At this point I can output a figure that has the sensitivity curve data
  for each of the five parameters. The figure with the artificial data and
  fitted curve with error bars will be shown next.*/

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
  popteaCore.LMA.LMA_workspace.emissionExperimental =
  thermal::emission::addNoise( myEmissionNoise,
                               popteaCore.expSetup.laser.l_thermal,
                               popteaCore.LMA.LMA_workspace.emissionNominal ) ;

//  ///Output noise to test
//  for( size_t i = 0 ; i < popteaCore.expSetup.laser.l_thermal.size() ; ++i)
//  {
//    std::cout <<  popteaCore.expSetup.laser.l_thermal[i] << "\t"
//              <<  popteaCore.LMA.LMA_workspace.emissionNominal[i] << "\t"
//              <<  popteaCore.LMA.LMA_workspace.emissionExperimental[i] << "\n" ;
//  }

  /// STEP 1
  int nfev;
  int info = 0;
  popteaCore.LMA.xpredicted = paramter_estimation( popteaCore, &info, &nfev );

//  for( size_t i = 0 ; i < popteaCore.LMA.xpredicted.size() ;  i++)
//  {
//    std::cout << popteaCore.LMA.xpredicted[i] << "\n";
//  }t

  /// STEP 2
  thermal::emission::phase99( popteaCore, popteaCore.LMA.LMA_workspace.predicted );
  popteaCore.LMA.LMA_workspace.MSE =
      MSE( popteaCore.expSetup.laser.L_end,
           popteaCore.LMA.LMA_workspace.emissionExperimental,
           popteaCore.LMA.LMA_workspace.predicted ) ;
  std::cout << popteaCore.LMA.LMA_workspace.MSE << "\n";

  /// STEP 3

  /// STEP 4
  class math::estimation::unknown
      first(popteaCore.LMA.unknownParameters.vectorUnknowns[0]);

  class math::sensitivityAnalysis::step4 Step4;
  std::cout << "this is the output\n\n" << Step4.solve();

  return;
}





}
}

