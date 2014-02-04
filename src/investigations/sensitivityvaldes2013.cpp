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

void run( const filesystem::directory dir )
{
  ///Initialize kernals
  const class thermal::analysis::Kernal
      popteaCore = thermal::analysis::loadWorkingDirectoryKernal(dir);
  class thermal::analysis::Poptea
      poptea = thermal::analysis::loadWorkingDirectoryPoptea ( dir, popteaCore);

  //Noise in Simulated Emission
  constexpr double a =  .01*0;        // max % error (%*pi/2) (try .025)
  constexpr double b = 2.95;        // stretching parameter  (try 2.95) (1->pi)
  constexpr bool d1 = true;         //positive  (try false)
  constexpr bool d2 = true;         //monotonic (try true)
  constexpr int s1 = 0;             //-1(left bias) 0(symmetric) +1(right bias)
  constexpr double noiseRandom = 0.01*0;              // normal noise % of pi/2
  const thermal::emission::ExpNoiseSetting
      myEmissionNoise( a, b, d1, d2, s1, noiseRandom );

  ///Output noise to test
  std::vector<double> emissionNominal =
      thermal::emission::phase99(*(poptea.coreSystem), poptea.thermalData->omegas);

  std::vector<double> emissionExperimental = thermal::emission::
      addNoise( emissionNominal, poptea.thermalSweep(), myEmissionNoise ) ;

  poptea.updateExperimentalData( poptea.thermalData->omegas ,
                                 emissionExperimental );

//  poptea.bestFit();
//  poptea.parameterIntervalEstimates();
//  poptea.optimization();

////////////////////////////////////////////////////////////////////////////////



///what am i minimizing exactly? it's not best fit, it's the tolerance on the
/// parameters.  So I need to pick one
/// optimizer( "asub" , 5 );  //finds best data but stops when asub is 5%
/// optimizer( "asum" ) ///finds best data
/// now it should populate my unknown parameters list with a final best fit
/// it should iterate through the process and return all my estimations
/// it should return the C/R necessary and the lmin, lmax
/// it should be constrained to my original experimental data
/// it should










  return;
}





}
}

