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
#include "tools/interface/exportfile.hpp"

namespace thermal{
namespace analysis{

Poptea
initializePopTeawithNominalEmission( const filesystem::directory &dir )
{
  ///Initialize kernals
  const Kernal popteaCore = loadWorkingDirectoryKernal( dir ) ;
  Poptea poptea = loadWorkingDirectoryPoptea ( dir, popteaCore ) ;
  
  ///Output noise to test
  using thermal::emission::phase99;
  typedef const std::vector<double> sweep;
  sweep emissionNominal = phase99( *(poptea.coreSystem) , poptea.thermalData->omegas ) ;
  
  

  poptea.updateExperimentalData( poptea.thermalData->omegas , emissionNominal );
  


  
  return poptea;
}
 
  
Poptea
initializePopTeaAndLoadSimuEmission( const filesystem::directory &dir )
{
  using std::vector;
  
  // Retrieve nominal emission from the poptea initial
  Poptea poptea = initializePopTeawithNominalEmission( dir );
  const vector<double>
  emissionNominal = poptea.thermalData->experimentalEmission;
  
  //Noise in Simulated Emission
  using thermal::emission::ExpNoiseSetting;
  const ExpNoiseSetting myEmissionNoise =ExpNoiseSetting::loadExpNoiseFile(dir);
  
  using thermal::emission::addNoise;
  const vector<double> emissionExperimental =
  addNoise( emissionNominal, poptea.thermalSweep(), myEmissionNoise ) ;
  
  poptea.updateExperimentalData( poptea.thermalData->omegas ,
                                 emissionExperimental ) ;
  
  
  typedef const std::string print_this_string;
  print_this_string emission_raw =
  poptea.thermalData->prettyPrint( poptea.coreSystem->TBCsystem.coating, emissionNominal ) ;
  using tools::interface::exportfile;
  exportfile( dir.pwd() + "/" + "thermalSweep.dat" , emission_raw ) ;
  
  return poptea;
}
  
}}