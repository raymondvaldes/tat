/*----------------------------------------------------------------------------*\
 ========                  |
    ||     T Thermal       | TAT: Thermal Analysis Toolbox
    ||     A Analysis      |
    ||     T Toolbox       | Copyright (C) 2013 Raymond Valdes
    ||                     |
 --------------------------------------------------------------------------------
 License
 This file is part of Thermal Analysis Toolbox.
 
 Thermal Analysis Toolbox is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or (at your
 option) any later version.
 
 Thermal Analysis Toolbox is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 Public License for more details.
 
 You should have received a copy of the GNU General Public License along with
 Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.
 
\*----------------------------------------------------------------------------*/

#include "thermal/analysis/poptea_initialize.h"
#include "thermal/emission/noise.hpp"
#include "thermal/emission/phase99.hpp"

namespace thermal{
namespace analysis{

Poptea
initializePopTeaAndLoadSimuEmission( const filesystem::directory &dir )
{
  ///Initialize kernals
  const Kernal popteaCore = loadWorkingDirectoryKernal( dir ) ;
  Poptea poptea = loadWorkingDirectoryPoptea ( dir, popteaCore);
  
  //Noise in Simulated Emission
  using thermal::emission::ExpNoiseSetting;
  const ExpNoiseSetting myEmissionNoise =ExpNoiseSetting::loadExpNoiseFile(dir);
  
  ///Output noise to test
  using thermal::emission::phase99;
  const std::vector<double> emissionNominal =
  phase99( *(poptea.coreSystem) , poptea.thermalData->omegas ) ;
  
  using thermal::emission::addNoise;
  const std::vector<double> emissionExperimental =
  addNoise( emissionNominal, poptea.thermalSweep(), myEmissionNoise ) ;
  
  poptea.updateExperimentalData( poptea.thermalData->omegas ,
                                emissionExperimental ) ;
  
  return poptea;
}
  
}}