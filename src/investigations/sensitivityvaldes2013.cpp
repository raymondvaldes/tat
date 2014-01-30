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

namespace investigations
{
namespace sensitivityvaldes2013
{

void run(const class filesystem::directory dir)
{
  ///Initialize kernals
  class thermal::analysis::Kernal
      popteaCore = thermal::analysis::loadWorkingDirectoryKernal(dir);
  class thermal::analysis::Poptea
      poptea = thermal::analysis::loadWorkingDirectoryPoptea ( dir, popteaCore);

  /// STEP 0
  //Noise in Simulated Emission
  constexpr double a =  .01;   // max % error (%*pi/2) (try .025)
  constexpr double b = 2.95;   // stretching parameter  (try 2.95) (1->pi)
  constexpr bool d1 = true;    //positive  (try false)
  constexpr bool d2 = true;    //monotonic (try true)
  constexpr int s1 = 0;        //-1(left bias) 0(symmetric) +1(right bias)
  constexpr double noiseRandom = 0.01*0; // normal noise % of pi/2
  const class thermal::emission::ExpNoiseSetting
      myEmissionNoise( a, b, d1, d2, s1, noiseRandom );

  ///Output noise to test
  const size_t Lend = poptea.thermalData.omegas.size();
  std::vector<double> emissionNominal( Lend ) ;
  emissionNominal = thermal::emission::phase99( poptea.coreSystem ,
                                                poptea.thermalData.omegas );

  std::vector<double> emissionExperimental( Lend );
  emissionExperimental = thermal::emission::
      addNoise( emissionNominal, poptea.thermalData.l_thermal, myEmissionNoise);

  poptea.updateExperimentalData( poptea.thermalData.omegas ,
                                 emissionExperimental );
  poptea.parameterIntervalEstimates();


  std::cout << "iterate through parameters now:---\n\n";
  std::cout << "parameter estimates intervals:\n";
  std::cout << "------------------------------\n\n";
  std::cout << "min\t\tbestfit\t\tmax\n";

  for(auto& val : poptea.LMA.unknownParameters() )
  {
    std::cout << val.bestfitInterval.lower << "\t\t"   <<  val.bestfit()
              << "\t\t"   << val.bestfitInterval.upper << "\n";
//    std::cout << "search bounds(" << lowerbound << ", " << upperbound <<")\n\n";
  }



  return;
}





}
}

