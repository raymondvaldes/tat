/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__poptea_initialize__
#define __tat__poptea_initialize__

#include "thermal/analysis/poptea.hpp"

namespace thermal{
namespace analysis{

Poptea
initializePopTeawithNominalEmission( const filesystem::directory &dir )
noexcept;

Poptea
initializePopTeaAndLoadSimuEmission( const filesystem::directory &dir )
noexcept;

Poptea
initializePopTeawithExperimentalEmission( const filesystem::directory &dir )
noexcept;
  
} // namespace analysis
} // namespace thermal

#endif /* defined(__tat__poptea_initialize__) */
