/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <algorithm>

#include "thermal/analysis/poptea_initialize.h"
#include "thermal/emission/noise.hpp"
#include "thermal/emission/phase99.hpp"
#include "tools/interface/exportfile.hpp"

namespace thermal{
namespace analysis{

Poptea
initializePopTeawithNominalEmission( const filesystem::directory &dir ) noexcept
{
  ///Initialize kernals
  const Kernal popteaCore = loadWorkingDirectoryKernal( dir ) ;
  Poptea poptea = loadWorkingDirectoryPoptea ( dir, popteaCore ) ;

  ///Output noise to test
  using thermal::emission::phase99;
  typedef const std::vector<double> sweep;
  sweep emissionNominal = phase99( *(poptea.coreSystem) ,
    poptea.thermalData->omegas ) ;
  
  poptea.updateModelData( poptea.thermalData->omegas, emissionNominal ) ;
  poptea.updateExperimentalData( poptea.thermalData->omegas , emissionNominal );
  
  return poptea;
}

Poptea
initializePopTeawithExperimentalEmission( const filesystem::directory &dir )
  noexcept
{
  using units::quantity;
  using units::si::electric_potential;
  
  Poptea poptea = initializePopTeawithNominalEmission( dir );
  return poptea;
}


Poptea
initializePopTeaAndLoadSimuEmission( const filesystem::directory &dir ) noexcept
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
