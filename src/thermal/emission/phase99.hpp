/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef PHASE99_HPP
#define PHASE99_HPP

#include <vector>
#include "thermal/analysis/kernal.hpp"
#include "thermal/model/labels.h"

namespace thermal{
  namespace emission{

std::vector<double>
phase99( const thermal::analysis::Kernal &popteaCore,
         const std::vector<double> &omegas) noexcept;


std::vector<double> phase99Pertrub(
  const thermal::analysis::Kernal &popteaCore,
  const std::vector<double> &omegas,
  const std::vector< std::pair < enum model::labels::Name, double > > list,
  const size_t ith ) noexcept;



  }
}
#endif // PHASE99_HPP
