/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef SENSITIVITYVALDES2013_HPP
#define SENSITIVITYVALDES2013_HPP

#include "thermal/analysis/kernal.hpp"
#include "tools/interface/filesystem.hpp"

#include "thermal/analysis/poptea.hpp"

namespace investigations{
namespace sensitivityvaldes2013{

void run(const filesystem::directory &dir ) noexcept;
void demo( const filesystem::directory &dir ) noexcept;


}}

#endif // SENSITIVITYVALDES2013_HPP




