/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__model__
#define __tat__model__

#include <iostream>

namespace thermal{
  namespace define{
    
  
enum class HeatX: uint8_t
{
  OneDimAnalytical,
  OneDimNumLin,
  OneDimNumNonLin,
  TwoDimAnalytical,
  TwoDimNumLin,
  TwoDimNumNonLin
} ;


enum class EmissionX: uint8_t
{
  OneDimNonLin,
  TwoDimNonLin
} ;
    
    
  }
}


#endif /* defined(__tat__model__) */
