/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__File__
#define __tat__File__

#include <utility>
#include <string>
#include <vector>

namespace investigations {

void execute( const std::string& directory_of_samples,
              const std::string& sampleName,
              const std::string& investigationName ) noexcept;
}

#endif /* defined(__tat__File__) */
