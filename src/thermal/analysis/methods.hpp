/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
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
#ifndef METHODS_HPP
#define METHODS_HPP

#include <string>
#include <vector>
#include <memory>

#include "models/physicalmodel.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/pie.hpp"



namespace thermal{
namespace analysis{

class methods: private baseData
{

private:
  /// working objects
  std::shared_ptr< LMA > bestfitMethod;
  std::shared_ptr< PIE > intervalEstimates;
  std::shared_ptr< ThermalSweepOptimizer > lthermalSweepOptimizer;

public:
  //constructors
  methods( const math::estimation::settings &Settings_in,
           const math::estimation::unknownList &unknownParameters_in,
           const ThermalData& thermalData_in ) ;

  //output methods
  double bestFit(
      std::shared_ptr< math::estimation::unknownList > &list_in,
      std::shared_ptr< ThermalData > &thermalData_in,
      std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) ;

  void parameterIntervalEstimates(
      std::shared_ptr< math::estimation::unknownList > &list_in,
      std::shared_ptr< ThermalData > &thermalData_in,
      std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) ;

  void optimization(
      std::shared_ptr< math::estimation::unknownList > &list_in,
      std::shared_ptr< ThermalData > &thermalData_in,
      std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in );
};

}}

#endif // METHODS_HPP